//
// Created by CherryBlossomNight on 2023/11/28.
//

#include "differential_controller/differential_controller.h"
#include <pluginlib/class_list_macros.hpp>
#include <sp_common/base_utilities.h>

namespace differential_controller
{
  bool DifferentialController::init(hardware_interface::RobotHW *robot_hw, ros::NodeHandle &root_nh, ros::NodeHandle &controller_nh)
  {
    ros::NodeHandle nh_positive = ros::NodeHandle(controller_nh, "positive_joint");
    ros::NodeHandle nh_negative = ros::NodeHandle(controller_nh, "negative_joint");

    differential_reduction_ = sp_common::getParam(controller_nh, "differential_reduction", 2);

    effort_joint_interface_ = robot_hw->get<hardware_interface::EffortJointInterface>();
    if (!ctrl_positive_.init(effort_joint_interface_, nh_positive) || !ctrl_negative_.init(effort_joint_interface_, nh_negative) )
        return false;
    
    pitch_cmd_sub_ = nh.subscribe<std_msgs::Float64>("pitch_cmd", 1, &DifferentialController::setPitchCommandCB, this);
    roll_cmd_sub_ = nh.subscribe<std_msgs::Float64>("roll_cmd", 1, &DifferentialController::setRollCommandCB, this);

    pitch_pos_pub_ = nh.advertise<std_msgs::Float64>("pitch_pos", 10);
    
    pitch_pos_ = (ctrl_positive_.joint_.getPosition() + ctrl_negative_.joint_.getPosition()) / 2;
    roll_pos_ = (ctrl_positive_.joint_.getPosition() - ctrl_negative_.joint_.getPosition()) / (2 * differential_reduction_);

    ROS_INFO("DIFFERENTIAL : Initializing Completed");

    
    return true;
  }

  void DifferentialController::update(const ros::Time &time, const ros::Duration &period)
  { 
    pitch_pos_ = (ctrl_positive_.joint_.getPosition() + ctrl_negative_.joint_.getPosition()) / 2;
    roll_pos_ = (ctrl_positive_.joint_.getPosition() - ctrl_negative_.joint_.getPosition()) / (2 * differential_reduction_);
    //if (ctrl_left_.joint_.getPosition() - ctrl_right_.joint_.getPosition())
    ROS_INFO_STREAM("pitch_pos_: " << pitch_pos_);
    ROS_INFO_STREAM("roll_pos_: " << roll_pos_);
    std_msgs::Float64 pitch_pos;
    pitch_pos.data = pitch_pos_;
    pitch_pos_pub_.publish(pitch_pos);

    ctrl_positive_.setCommand(pitch_cmd_ + differential_reduction_ * roll_cmd_);
    ctrl_negative_.setCommand(pitch_cmd_ - differential_reduction_ * roll_cmd_);
    ctrl_positive_.update(time, period);
    ctrl_negative_.update(time, period);

  }

  double DifferentialController::getPitchPosition()
  {
    return pitch_pos_;
  }

  double DifferentialController::getRollPosition()
  {
    return roll_pos_;
  }

  void DifferentialController::setPitchCommand(double pitch_cmd)
  {
    pitch_cmd_ = pitch_cmd;
  }

  void DifferentialController::setRollCommand(double roll_cmd)
  {
    roll_cmd_ = roll_cmd;
  }

  void DifferentialController::setPitchCommandCB(const std_msgs::Float64::ConstPtr &pitch_cmd)
  {
    setPitchCommand(pitch_cmd->data);
  }

  void DifferentialController::setRollCommandCB(const std_msgs::Float64::ConstPtr &roll_cmd)
  {
    setRollCommand(roll_cmd->data);
  }


} // namespace differential_controller

PLUGINLIB_EXPORT_CLASS(differential_controller::DifferentialController, controller_interface::ControllerBase)