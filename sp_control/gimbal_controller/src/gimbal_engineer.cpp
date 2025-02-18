#include "gimbal_controller/gimbal_engineer.h"
#include <angles/angles.h>
#include <string>
#include <pluginlib/class_list_macros.hpp>

namespace gimbal_controller
{
    template <typename T>
    T getParam(ros::NodeHandle &pnh, const std::string &param_name, const T &default_val)
    {
        T param_val;
        pnh.param<T>(param_name, param_val, default_val);
        return param_val;
    }

    bool GimbalEngineer::init(hardware_interface::RobotHW *robot_hw, ros::NodeHandle &root_nh, ros::NodeHandle &controller_nh)
    {
        GimbalBase::init(robot_hw, root_nh, controller_nh);
        ros::NodeHandle nh_yaw = ros::NodeHandle(controller_nh, "yaw");
        ros::NodeHandle nh_pitch = ros::NodeHandle(controller_nh, "pitch");
        // get the position joint interface
        effort_joint_interface_ = robot_hw->get<hardware_interface::EffortJointInterface>();
        position_joint_interface_ = robot_hw->get<hardware_interface::PositionJointInterface>();

        gimbal_cali_sub_ = root_nh.subscribe<std_msgs::Bool>("/gimbal_calibration", 1, &GimbalEngineer::GimbalCaliCallback, this);
      
        angle_pub_ = root_nh.advertise<std_msgs::Float64>("yaw_angle", 10);

        // subsribe the topic "cmd_pos"
       
        if (!ctrl_yaw_.init(effort_joint_interface_, nh_yaw) || !ctrl_pitch_.init(position_joint_interface_, nh_pitch))
            return false;
        // construct vector<joint> to control the acuators directly.
        ROS_INFO("GIMBAL: INIT SUCCESS !");

        return true;
    }

    
    void GimbalEngineer::update(const ros::Time &time, const ros::Duration &period)
    {
        if (!init_pos_)
        {
            getPosition(time, period);
            init_pos_ = true;
        }

        if (!init_cmd_)
        {
            yaw_cmd_ = yaw_pos_;
            init_cmd_ = true;
        }

        if (!initiated_)
        {
            getPosition(time, period);
        }
        
        cmd_vel_ = cmd_rt_buffer_.readFromRT()->cmd_gimbal_vel_;
        double yaw_angle = ctrl_yaw_.joint_.getPosition();
        std_msgs::Float64 yaw;
         if (!initiated_)
            yaw.data = yaw_angle;
        else
            yaw.data = yaw_angle + yaw_pos_;
        angle_pub_.publish(yaw);
        
        moveJoint(time, period);
    }

    void GimbalEngineer::getPosition(const ros::Time &time, const ros::Duration &period)
    {
        yaw_pos_ = ctrl_yaw_.joint_.getPosition();
    }

    void GimbalEngineer::cmdConstraint()
    {

        if (yaw_cmd_ > 1.57)
            yaw_cmd_ = 1.57;
        else if (yaw_cmd_ < -1.57)
            yaw_cmd_ = -1.57;

        if (pitch_pos_ > 0.7)
            pitch_pos_ = 0.7;
        else if (pitch_pos_ < -0.9)
            pitch_pos_ = -0.9;

        
    }


    void GimbalEngineer::moveJoint(const ros::Time &time, const ros::Duration &period)
    {
        if (abs(cmd_vel_.z) < 0.05)
            yaw_cmd_ += cmd_vel_.z;
        pitch_pos_+= cmd_vel_.y;
        cmdConstraint();
        //ROS_INFO_STREAM(yaw_cmd_);
        // ROS_INFO_STREAM(ctrl_yaw_.joint_.getPosition());
        // ROS_INFO_STREAM("---------------------");
        
        if (!initiated_)
            ctrl_yaw_.setCommand(yaw_cmd_);
        else
            ctrl_yaw_.setCommand(yaw_cmd_ + yaw_pos_);
     
     
        ctrl_yaw_.update(time, period);
        ctrl_pitch_.joint_.setCommand(pitch_pos_);
    }

    void GimbalEngineer::GimbalCaliCallback(const std_msgs::Bool::ConstPtr &msg)
    {
        if (msg->data)
        {
            if (!initiated_)
            {
                initiated_ = true;
            }
            yaw_cmd_ = 0.0;
        }
    }

    PLUGINLIB_EXPORT_CLASS(gimbal_controller::GimbalEngineer, controller_interface::ControllerBase);
} // namespace gimbal_controller
