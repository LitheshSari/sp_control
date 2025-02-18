#pragma once
#include <unordered_map>

#include <controller_interface/multi_interface_controller.h>
#include <hardware_interface/joint_command_interface.h>
#include <realtime_tools/realtime_publisher.h>
#include <effort_controllers/joint_position_controller.h>
#include <syn_controller/syn_controller.h>
#include <differential_controller/differential_controller.h>

#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64MultiArray.h>


#include <tf2_msgs/TFMessage.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Quaternion.h>
#include <nav_msgs/Odometry.h>

#include <sp_common/filters/filters.h>
#include <sp_common/base_utilities.h>
#include <sp_common/ManipulatorCmd.h>
#include <sp_common/CustomerControllerCmd.h>
#include <sp_common/VisionCmd.h>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include "manipulator_controller/spline.h"
namespace manipulator_controller
{
    struct Command
    {
        geometry_msgs::Quaternion cmd_quat_;
        geometry_msgs::Twist cmd_twist_;
        std_msgs::Float64MultiArray cmd_joint_vel_;
        sp_common::ManipulatorCmd cmd_manipulator_;
        sp_common::CustomerControllerCmd cmd_cc_;
        //geometry_msgs::Pose cmd_vision_;
        std_msgs::Float64MultiArray cmd_vision_;
        ros::Time stamp_;
    };

    

    // struct Structure_coeff
    // {
    //     double l1_;
    //     double l2_;
    //     double l3_;
    //     double l4_;
    // };


    class ManipulatorController : public controller_interface::MultiInterfaceController<hardware_interface::EffortJointInterface>
    {
    public:
        ManipulatorController() = default;
        /** @brief Get and check params for covariances. Setup odometry realtime publisher + odom message constant fields.
         * init odom tf.
         *
         * @param robot_hw The robot hardware abstraction.
         * @param root_nh A NodeHandle in the root of the controller manager namespace. This is where the ROS interfaces are
         * setup (publishers, subscribers, services).
         * @param controller_nh A NodeHandle in the namespace of the controller. This is where the controller-specific
         * configuration resides.
         * @return True if initialization was successful and the controller
         * is ready to be started.
         */
        bool init(hardware_interface::RobotHW *robot_hw, ros::NodeHandle &root_nh, ros::NodeHandle &controller_nh) override;
        /** @brief Receive real_time command from manual. Execute different action according to current mode. Set
         * necessary params of chassis. Execute power limit.
         *
         * Receive real_time command from manual and check whether it is normally, if can not receive command from manual
         * for a while, chassis's velocity will be set zero to avoid out of control. Execute different action according
         * to current mode such as RAW, FOLLOW, GYRO, TWIST.(Their specific usage will be explain in the next). UpdateOdom,Set
         * necessary params such as Acc and vel_tfed. Execute moving action and powerlimit.
         *
         * @param time The current time.
         * @param period The time passed since the last call to update.
         */
        void update(const ros::Time &time, const ros::Duration &period) override;
        void starting(const ros::Time &time) {}
        void stopping(const ros::Time &time) {}

    protected:
        void moveJoint(const ros::Time &time, const ros::Duration &period);

        void initPosition(const ros::Time &time, const ros::Duration &period);

        void caliMode();

        void maulMode();

        void autoMode();

        void jointMode();

        void destinationMode();

        void visionMode();

        void processMode();

        void generateSplineCoeff(int index);

        void calJointVel();

        void getPosition();

        void updateJacobian();

        void finalPush();

        void visionInverseKinematic();
        
        void jointPosConstraint();

        void orePlaceProcess();

        void msgCaliZCallback(const std_msgs::Bool::ConstPtr &msg);

        void msgCaliXCallback(const std_msgs::Bool::ConstPtr &msg);

        void msgCaliYCallback(const std_msgs::Bool::ConstPtr &msg);

        void msgCaliPitchCallback(const std_msgs::Bool::ConstPtr &msg);

        void cmdQuatCallback(const geometry_msgs::Quaternion::ConstPtr &msg);

        void cmdTwistCallback(const geometry_msgs::Twist::ConstPtr &msg);

        void cmdJointVelCallback(const std_msgs::Float64MultiArray::ConstPtr &msg);

        void cmdManipulatorCallback(const sp_common::ManipulatorCmd::ConstPtr &msg);

        void cmdCustomerControllerCallback(const sp_common::CustomerControllerCmd::ConstPtr &msg);

        //void cmdVisionCallback(const geometry_msgs::Pose::ConstPtr &msg);
        void cmdVisionCallback(const std_msgs::Float64MultiArray::ConstPtr &msg);

        void stopProcess();

        void readyProcess();

        bool simulate_{};

        double publish_rate_{}, timeout_{};

        hardware_interface::EffortJointInterface *effort_joint_interface_{};

        syn_controller::SynController ctrl_z_, ctrl_x_;

        effort_controllers::JointPositionController ctrl_y_;

        effort_controllers::JointPositionController ctrl_yaw_, ctrl_roll1_;

        effort_controllers::JointPositionController ctrl_pitch_, ctrl_roll2_;

        differential_controller::DifferentialController ctrl_diff_;

        ros::Time last_publish_time_;

        std::vector<double> vel_limit_{};
        std::vector<double> upper_pos_limit_{};
        std::vector<double> lower_pos_limit_{}; 
        std::vector<double> position_threshold_{}; 
        std::unordered_map<std::string, std::vector<double>> joint_destination_;
        std::vector<double> vision_destination_{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        std::unordered_map<std::string, int> joint_process_num_;
        std::unordered_map<std::string, double> process_delay_time_;
        std::unordered_map<std::string, std::vector<std::vector<double>>> joint_process_;
        std::string destination_name_;
        std::string process_name_;

        //geometry_msgs::Pose vision_pose_; 
        Eigen::Matrix<double, 6, 1> vision_pose_;

        Eigen::Quaterniond quat_cmd_{};

        Eigen::Matrix<double, 6, 1> twist_cmd_{};
        Eigen::Matrix<double, 7, 1> joint_cmd_{}, joint_vel_cmd_{}, joint_pos_{}, joint_pos_cmd_{};
        Eigen::Matrix<double, 7, 4> coeff_{};
        sp_common::ManipulatorCmd manipulator_cmd_{};
        sp_common::CustomerControllerCmd cc_cmd_{};


        Eigen::Matrix<double, 3, 4> jacobian {};
        // Subscribers
        ros::Subscriber cmd_quat_sub_;
        ros::Subscriber cmd_twist_sub_;
        ros::Subscriber cmd_joint_vel_sub_;
        ros::Subscriber cmd_manipulator_sub_;
        ros::Subscriber cmd_cc_sub_;
        ros::Subscriber cmd_vision_sub_;

        ros::Publisher cali_pub_;
        ros::Publisher vision_pub_;
        ros::Publisher pos_pub_;
        
        ros::Subscriber msg_joint_z_cali_sub_;
        ros::Subscriber msg_joint_x_cali_sub_;
        ros::Subscriber msg_joint_y_cali_sub_;
        ros::Subscriber msg_joint_pitch_cali_sub_;

        bool initiated_{};

        bool z_calimsg_{};
        bool x_calimsg_{};
        bool y_calimsg_{};
        bool pitch_calimsg_{}; 

        bool z_calibrated_{};
        bool x_calibrated_{};
        bool y_calibrated_{};
        bool pitch_calibrated_{}; 
        bool calibrated_{};

        bool cali_{};

        double z_offset_{}, x_offset_{}, y_offset_{}, pitch_offset_{};

        enum
        {
            MAUL,
            AUTO,
            JOINT,
            CALI
        };

        enum
        {
            DESTINATION,
            PROCESS
        };

        enum
        { 
            NONE, 
            HOME,
            GROUND,
            SLIVER,
            GOLD,
            EXCHANGE,
            VISION
        };

        enum
        { 
            STOP,
            TAKE_SLIVER,
            TAKE_GLOD,
        };


        int mode_ = MAUL;
        bool mode_changed_ = false;

        int auto_type_ = DESTINATION;

        bool y_has_friction_{};
        double y_friction_{};

        bool last_final_push_{}, final_push_{};

        bool planed_, begin_exchange_, vision_execuated_;

        int destination_ = NONE;
        int process_ = STOP;
        int process_num_ = 0;

        Spline spline_;

        ros::Time begin_time_, now_time_, reach_time_;

        control_toolbox::Pid y_lock_pid_;
        bool y_lock_{};



        Command cmd_struct_;
        realtime_tools::RealtimeBuffer<Command> cmd_rt_buffer_;

     
    };

}

