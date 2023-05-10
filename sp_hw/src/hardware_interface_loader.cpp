// ref https://github.com/ros-controls/ros_control/wiki/hardware_interface
// ref rm_control.git

#include "sp_hw/hardware_interface_loader.hpp"
/*! TODO :  for the thread priority we should seperate the can_bus thread and
 *          SpRobotLoader::update() thread.
 */
namespace sp_hw
{
    SpRobotHWLoader::SpRobotHWLoader(ros::NodeHandle &nh, std::shared_ptr<SpRobotHW> hardware_interface)
        : nh_(nh), hardware_interface_(std::move(hardware_interface))
    {
        // Load ros params
        int error = 0, thread_priority;
        ros::NodeHandle nh_p("~");
        error += !nh_p.getParam("loop_frequency", loop_hz_);
        error += !nh_p.getParam("cycle_time_error_threshold", cycle_time_error_threshold_);
        error += !nh_p.getParam("thread_priority", thread_priority);
        if (error > 0)
        {
            char error_message[] = "could not retrieve one of the required parameters :\n\tsp_hw/loop_hz or "
                                   "sp_hw/cycle_time_error_threshold or "
                                   "sp_hw/thread_priority";
            ROS_ERROR_STREAM(error_message);
            throw std::runtime_error(error_message);
        }

        // Initialise the hardware interface:
        // 1. retrieve configuration from rosparam
        // 2. initialise the hardware and interface it with ros_control
        hardware_interface_->setCanBusThreadPriority(thread_priority);
        hardware_interface_->init(nh, nh_p);
        // Create the controller manager
        controller_manager_.reset(new controller_manager::ControllerManager(hardware_interface_.get(), nh_));

        // Get current time for use with first update
        last_time_ = clock::now();
        loop_running_ = true;
        //  Setup loop thread
        loop_thread_ = std::thread([&]()
                                   {
            while (loop_running_)
            {
                
                if (loop_running_)
                    update();
            } 
                ROS_INFO("[SP_HW] thread deconstructed."); });
        ROS_INFO("\033[42;37m [SP_HW] Successfully started HW_LOOP thread with ID %lu \033[0m", loop_thread_.native_handle());
        sched_param sched{.sched_priority = thread_priority};
        if (pthread_setschedparam(loop_thread_.native_handle(), SCHED_FIFO, &sched) != 0)
            ROS_WARN_STREAM("Failed to set threads priority (one possible reason could be that the user and the group permissions "
                            "are not set properly.)\n : "
                            << std::strerror(errno) << std::endl);
    }

    void SpRobotHWLoader::update()
    {
        const auto current_time = clock::now();
        // Compute desired duration rounded to clock decimation
        const duration<double> desired_duration(1.0 / loop_hz_);
        // Get change in time
        duration<double> time_span = duration_cast<duration<double>>(current_time - last_time_);
        elapsed_time_ = ros::Duration(time_span.count());
        last_time_ = current_time;

        // Check cycle time for excess delay
        const double cycle_time_error = (elapsed_time_ - ros::Duration(desired_duration.count())).toSec();
        if (cycle_time_error > cycle_time_error_threshold_)
            ROS_WARN_STREAM("Cycle time exceeded error threshold by: " << cycle_time_error - cycle_time_error_threshold_
                                                                       << "s, "
                                                                       << "cycle time: " << elapsed_time_ << "s, "
                                                                       << "threshold: " << cycle_time_error_threshold_ << "s");
        // Input
        // get the hardware's state
        hardware_interface_->read(ros::Time::now(), elapsed_time_);

        // Control
        // let the controller compute the new command (via the controller manager)
        controller_manager_->update(ros::Time::now(), elapsed_time_);

        // Output
        // send the new command to hardware
        // TODO : (Lithesh) until we have urdf and then use this line
        hardware_interface_->write(ros::Time::now(), elapsed_time_);
        // hardware_interface_->publishActuatorState(ros::Time::now());

        // Sleep
        const auto sleep_till = current_time + duration_cast<clock::duration>(desired_duration);
        std::this_thread::sleep_until(sleep_till);
    }

    SpRobotHWLoader::~SpRobotHWLoader()
    {
        loop_running_ = false;
        if (loop_thread_.joinable())
            loop_thread_.join();
        ROS_INFO("[SP_HW] HW deconstructed.");
    }
} // namespace sp_hw