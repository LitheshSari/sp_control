#include "sp_operator/engineer.h"


namespace sp_operator
{

    bool Engineer::init()
    {
        Operator::init();
        ROS_INFO_STREAM("Engineer");
        controller_nh = ros::NodeHandle("engineer");
        manipulator_cmd_pub_ = nh.advertise<sp_common::ManipulatorCmd>("/cmd_manipulator", 10);
        twist_cmd_pub_ = nh.advertise<geometry_msgs::Twist>("/cmd_twist",10);
        joint_cmd_pub_ = nh.advertise<std_msgs::Float64MultiArray>("/cmd_joint_vel",10);
        ore_cmd_pub_ = nh.advertise<std_msgs::Int8>("/cmd_ore",1);
        pump_cmd_pub_ = nh.advertise<std_msgs::Bool>("/cmd_pump",10);
        rod_cmd_pub_ = nh.advertise<std_msgs::Bool>("/cmd_rod",1);
        chassis_deflected_pub_ = nh.advertise<std_msgs::Bool>("/cmd_def",10);
        gimbal_calibration_pub_ = nh.advertise<std_msgs::Bool>("/gimbal_calibration",10);
        velocity_sub_ = nh.subscribe<geometry_msgs::Twist>("/cmd_velocity", 10, &Engineer::velocity_callback, this);
        timeout_ = sp_common::getParam(controller_nh, "timeout", 2.0);
        x_coeff_ = sp_common::getParam(controller_nh, "chassis/x_coeff", 2.0);
        y_coeff_ = sp_common::getParam(controller_nh, "chassis/y_coeff", 2.0);
        z_mk_coeff_ = sp_common::getParam(controller_nh, "chassis/z_mk_coeff", 70);
        z_rc_coeff_ = sp_common::getParam(controller_nh, "chassis/z_rc_coeff", 1.5);
        x_accel_set_ = sp_common::getParam(controller_nh, "chassis/x_accel_set", 5);
        y_accel_set_ = sp_common::getParam(controller_nh, "chassis/y_accel_set", 5);
        z_accel_set_ = sp_common::getParam(controller_nh, "chassis/z_accel_set", 1.8);

        yaw_coeff_ =  sp_common::getParam(controller_nh, "gimbal/yaw_coeff", 0.005);
        pitch_mk_coeff_ = sp_common::getParam(controller_nh, "gimbal/pitch_mk_coeff", 0.005);
        pitch_rc_coeff_ = sp_common::getParam(controller_nh, "gimbal/pitch_rc_coeff", 0.005);
        yaw_left_limit_ = sp_common::getParam(controller_nh, "gimbal/yaw_left_limit", -1.57);
        yaw_right_limit_ = sp_common::getParam(controller_nh, "gimbal/yaw_right_limit", 1.57);
        pitch_low_limit_ = sp_common::getParam(controller_nh, "gimbal/pitch_low_limit", -0.52);
        pitch_high_limit_ = sp_common::getParam(controller_nh, "gimbal/pitch_high_limit", 0.52);
        // for (int i = 0; i < 7; i++)
        //     joint_cmd_.velocities.push_back(0.0);
        joint_vel_cmd_.data = std::vector<double>(7, 0.0);

        return true;
    }

    void Engineer::run()
    {

        

        chassis_cmd_pub_.publish(chassis_cmd_);

        gimbal_set();
        cmd_gimbal_vel_pub_.publish(cmd_gimbal_vel_); 
        

        gimbal_calibration_pub_.publish(gimbal_cali_cmd_);
        
        manipulator_set();
        manipulator_cmd_pub_.publish(manipulator_cmd_);
        twist_cmd_pub_.publish(twist_cmd_);

        joint_cmd_pub_.publish(joint_vel_cmd_);
        ore_cmd_pub_.publish(ore_cmd_);
        pump_cmd_pub_.publish(pump_cmd_);
        rod_cmd_pub_.publish(rod_cmd_);
        chassis_deflected_pub_.publish(deflection_cmd_);
        ros::Time time = ros::Time::now();
        if ((time - dbus_data_.stamp).toSec() > timeout_)
        {
            ROS_INFO_STREAM("Dbus lost");
            return;
        }
        chassis_set();
        cmd_chassis_vel_pub_.publish(cmd_chassis_vel_); 


        last_dbus_data_ = dbus_data_;
        ros::spinOnce();
    }


    void Engineer::chassis_set()
    {
        manipulator_cmd_.y_lock = false;

        if (dbus_data_.s_l == 3 && dbus_data_.s_r == 1) //Mouse & Keyboard mode
        {
            if (!deflection_cmd_.data)
            {
                cmd_chassis_vel_.linear.x = x_coeff_ * dbus_data_.ch_r_x;
                cmd_chassis_vel_.linear.y = -y_coeff_ * dbus_data_.ch_r_y;
            }
            else
            {
                cmd_chassis_vel_.linear.x = -x_coeff_ * dbus_data_.ch_r_y;
                cmd_chassis_vel_.linear.y = -y_coeff_ * dbus_data_.ch_r_x;
            }
            cmd_chassis_vel_.angular.z = -z_rc_coeff_ * dbus_data_.ch_l_x;
        }
        else if (dbus_data_.s_l == 3 && dbus_data_.s_r == 3) //Remote control mode
        {
            if (dbus_data_.key_w || dbus_data_.key_a ||
             dbus_data_.key_s || dbus_data_.key_d || abs(dbus_data_.m_x) > 0.2)
                manipulator_cmd_.y_lock = true;
            if (!deflection_cmd_.data)
            {
                if (dbus_data_.key_w)
                    cmd_chassis_vel_.linear.x = x_coeff_;
                else if (dbus_data_.key_s)
                    cmd_chassis_vel_.linear.x = -x_coeff_;
                else 
                    cmd_chassis_vel_.linear.x = 0.0;
                
                if (dbus_data_.key_a)
                    cmd_chassis_vel_.linear.y = y_coeff_;
                else if (dbus_data_.key_d)
                    cmd_chassis_vel_.linear.y = -y_coeff_;
                else 
                    cmd_chassis_vel_.linear.y = 0.0;
            }
            else
            {
                if (dbus_data_.key_w)
                    cmd_chassis_vel_.linear.y = -y_coeff_;
                else if (dbus_data_.key_s)
                    cmd_chassis_vel_.linear.y = y_coeff_;
                else 
                    cmd_chassis_vel_.linear.y = 0.0;
                
                if (dbus_data_.key_a)
                    cmd_chassis_vel_.linear.x = x_coeff_;
                else if (dbus_data_.key_d)
                    cmd_chassis_vel_.linear.x = -x_coeff_;
                else 
                    cmd_chassis_vel_.linear.x = 0.0;
            }
            cmd_chassis_vel_.angular.z = -z_mk_coeff_ * dbus_data_.m_x;
        }
        else if (dbus_data_.s_r == 2) //Stop mode
        {
            cmd_chassis_vel_.linear.x = 0.0;
            cmd_chassis_vel_.linear.y = 0.0;
            cmd_chassis_vel_.angular.z = 0.0;
        }
        else // Avoid chassis's movement when the manipulator is operating 
        {
            cmd_chassis_vel_.linear.x = 0.0;
            cmd_chassis_vel_.linear.y = 0.0;
            cmd_chassis_vel_.angular.z = 0.0;

        }

        chassis_cmd_.mode = NOFOLLOW; // Directly control z_velocity of chassis

        chassis_cmd_.accel.linear.x = x_accel_set_;
        chassis_cmd_.accel.linear.y = y_accel_set_;
        chassis_cmd_.accel.angular.z = z_accel_set_;
        chassis_cmd_.stamp = ros::Time::now();
    }

    void Engineer::gimbal_set()
    {
        if (dbus_data_.s_l == 3 && dbus_data_.s_r == 1) //Remote control mode
        {
            cmd_gimbal_vel_.y = pitch_rc_coeff_ * dbus_data_.ch_l_y;
            //cmd_gimbal_vel_.z = pitch_rc_coeff_ * dbus_data_.ch_l_x;
        }
        else if (dbus_data_.s_l == 2 && dbus_data_.s_r == 1)
        {
            cmd_gimbal_vel_.z = -pitch_rc_coeff_ * dbus_data_.ch_l_x;
        }
        else if (dbus_data_.s_r == 3) //Mouse & Keyboard  mode
        {
            if (dbus_data_.key_q && !dbus_data_.key_e) // Turn left
                cmd_gimbal_vel_.z = yaw_coeff_;
            else if (dbus_data_.key_e && !dbus_data_.key_q) // Turn right
                cmd_gimbal_vel_.z = -yaw_coeff_;
            // else if (dbus_data_.key_q && dbus_data_.key_e) // If press Q and E simultaneously, return to 0 position.
            //     cmd_gimbal_vel_.z = 1.0;
            // else if (dbus_data_.key_shift && dbus_data_.key_q)
            //     cmd_gimbal_vel_.z = 2.0;
            // else if (dbus_data_.key_shift && dbus_data_.key_e)
            //     cmd_gimbal_vel_.z = 3.0;
            else
                cmd_gimbal_vel_.z = 0.0;

            cmd_gimbal_vel_.y = -pitch_mk_coeff_ * dbus_data_.m_y;

            if (dbus_data_.key_r) // Gimbal calibration, set current position as the 0 potision.
                gimbal_cali_cmd_.data = true;
            else
                gimbal_cali_cmd_.data = false;

        }

    }
    
    void Engineer::manipulator_set()
    {

        if (dbus_data_.s_l == 1) // Maul mode, 
        {
            // Using a custom controller to control pose

            manipulator_cmd_.control_mode = MAUL;

            twist_cmd_.linear.x = 0;
            twist_cmd_.linear.y = 0;
            twist_cmd_.linear.z = 0;
            twist_cmd_.angular.x = 0.003 * velocity_cmd_.angular.x;
            twist_cmd_.angular.y = 0.003 * velocity_cmd_.angular.y;
            twist_cmd_.angular.z = 0.003 * velocity_cmd_.angular.z;
            if (dbus_data_.s_r == 1) //Control XYZ
            {
                // joint_vel_cmd_.data[0] = 0.0003 * dbus_data_.ch_l_x;
                // joint_vel_cmd_.data[1] = 0.01 * dbus_data_.ch_l_y;
                // joint_vel_cmd_.data[2] = 0.0015 * dbus_data_.ch_r_x;
                // joint_vel_cmd_.data[3] = 0.0005 * dbus_data_.ch_r_y;
                joint_vel_cmd_.data[0] = 0.001 * dbus_data_.ch_l_y;
                joint_vel_cmd_.data[1] = -0.001 * dbus_data_.ch_r_y;
                joint_vel_cmd_.data[2] = 0.0015 * dbus_data_.ch_r_x;
            }
          
            // twist_cmd_.angular.x = 0.001 * dbus_data_.ch_r_y;
            // twist_cmd_.angular.y = 0.001 * dbus_data_.ch_r_x;
            // twist_cmd_.angular.z = 0.001 * dbus_data_.ch_l_x;
        }
        else if (dbus_data_.s_l == 3)
        {
            manipulator_cmd_.control_mode = AUTO;
            manipulator_cmd_.destination = NONE;                   
            manipulator_cmd_.process = STOP;
            if (!dbus_data_.key_shift)
            {
                manipulator_cmd_.auto_type = DESTINATION;
                if (dbus_data_.key_z)
                    manipulator_cmd_.destination = HOME;
                else if (dbus_data_.key_x)
                    manipulator_cmd_.destination = GROUND;
                else if (dbus_data_.key_c)
                    manipulator_cmd_.destination = SLIVER;
                else if (dbus_data_.key_v)
                    manipulator_cmd_.destination = GOLD;
                else if (dbus_data_.key_b)
                    manipulator_cmd_.destination = EXCHANGE;
                // else if (dbus_data_.key_b && dbus_data_.key_shift)
                //     manipulator_cmd_.destination = VISION;
          
            }
            else
            {
                manipulator_cmd_.auto_type = PROCESS;
                if (dbus_data_.key_c)
                    manipulator_cmd_.process = TAKE_SLIVER;
                // else if (dbus_data_.key_v)
                //     manipulator_cmd_.process = TAKE_GOLD;
   
            }
        }
        else if (dbus_data_.s_l == 2)
        {
            manipulator_cmd_.control_mode = JOINT;
            if (dbus_data_.s_r == 1) //Remote control mode
            {
                // joint_vel_cmd_.data[0] = 0.0003 * dbus_data_.ch_l_x;
                // joint_vel_cmd_.data[1] = 0.01 * dbus_data_.ch_l_y;
                // joint_vel_cmd_.data[2] = 0.0015 * dbus_data_.ch_r_x;
                // joint_vel_cmd_.data[3] = 0.0005 * dbus_data_.ch_r_y;
                joint_vel_cmd_.data[0] = 0.001 * dbus_data_.ch_l_y;
                joint_vel_cmd_.data[1] = -0.001 * dbus_data_.ch_r_y;
                joint_vel_cmd_.data[2] = 0.0015 * dbus_data_.ch_r_x;
            }
            else if (dbus_data_.s_r == 3)
            {
                // joint_vel_cmd_.data[4] = -0.005 * dbus_data_.ch_r_x;
                // joint_vel_cmd_.data[5] = -0.005 * dbus_data_.ch_l_x;
                // joint_vel_cmd_.data[6] = -0.005 * dbus_data_.ch_r_y;
                joint_vel_cmd_.data[3] = 0.005 * dbus_data_.ch_l_y;
                joint_vel_cmd_.data[4] = -0.005 * dbus_data_.ch_l_x;
                joint_vel_cmd_.data[5] = 0.005 * dbus_data_.ch_r_x;
                joint_vel_cmd_.data[6] = 0.005 * dbus_data_.ch_r_y;
            }  
            else if (dbus_data_.s_r == 2)   
            {
                // ore_cmd_.data = -1.57 * dbus_data_.ch_l_y;
                // if (dbus_data_.key_w)
                //     ore_cmd_.data = 1;
                // else if (dbus_data_.key_s)
                //     ore_cmd_.data = 2;
                // else if (dbus_data_.key_a)
                //     ore_cmd_.data = 3;
                // else if (dbus_data_.key_d)
                //     ore_cmd_.data = 4;
                if(dbus_data_.ch_l_y < 0)
                    ore_cmd_.data = 1;               
                if(dbus_data_.ch_l_y > 0)
                    ore_cmd_.data = 2;
                if(dbus_data_.ch_l_x < 0)
                    ore_cmd_.data = 3;
                if(dbus_data_.ch_l_x > 0)
                    ore_cmd_.data = 4;
                if(dbus_data_.ch_r_y > 0)
                    ore_cmd_.data = 0;       
            }    
        }

        ros::Duration delay(0.05);
        pump_change_count_--;
        rod_change_count_--;
        deflection_change_count_--;
        calibration_change_count_--;
        // if (push_change_count_ <= 0)
        // {
        //     manipulator_cmd_.final_push = false;
        //     if (dbus_data_.key_g)
        //     {
        //         delay.sleep();
        //         if (dbus_data_.key_g)
        //         {
        //             manipulator_cmd_.final_push = true;
        //             push_change_count_ = 50;
        //         }
        //     }
        //     }
        if (calibration_change_count_ <= 0)
            manipulator_cmd_.cali = false;
        if (dbus_data_.key_r && calibration_change_count_ <= 0)
        {  
            delay.sleep();
            if (dbus_data_.key_r)
            {
                manipulator_cmd_.cali = true;
                calibration_change_count_ = 50;
            }
        }

        if (dbus_data_.key_g && deflection_change_count_ <= 0)
        {
            delay.sleep();
            if (dbus_data_.key_g)
            {
                if (!deflection_cmd_.data)
                    deflection_cmd_.data = true;
                else
                    deflection_cmd_.data = false;
                deflection_change_count_ = 50;
            }
        }
    

        if (dbus_data_.key_f && pump_change_count_ <= 0)
        {
            delay.sleep();
            if (dbus_data_.key_f)
            {
                if (!pump_cmd_.data)
                    pump_cmd_.data = true;
                else
                    pump_cmd_.data = false;
                pump_change_count_ = 50;
            }
        }

        if (dbus_data_.wheel > 0.8 && pump_change_count_ <= 0)
        {
            delay.sleep();
            if (dbus_data_.wheel > 0.8)
            {
                if (!pump_cmd_.data)
                    pump_cmd_.data = true;
                else
                    pump_cmd_.data = false;
                pump_change_count_ = 50;
            }
        }

        if (dbus_data_.key_ctrl && rod_change_count_ <= 0)
        {
            delay.sleep();
            if (dbus_data_.key_ctrl)
            {
                if (!rod_cmd_.data)
                    rod_cmd_.data = true;
                else
                    rod_cmd_.data = false;
                rod_change_count_ = 50;
            }
        }
            
                
    }
    void Engineer::velocity_callback(const geometry_msgs::Twist::ConstPtr &vel)
    {
        velocity_cmd_ = *vel;
    }  

 

}
    
    



