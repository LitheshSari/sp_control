/*******************************************************************************
 * BSD 3-Clause License
 *
 * Copyright (c) 2021, Qiayuan Liao
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/

//
// Created by qiayuan on 2019/10/30.
//

#ifndef SRC_RM_BRIDGE_INCLUDE_DBUS_NODE_H_
#define SRC_RM_BRIDGE_INCLUDE_DBUS_NODE_H_
#include "dbus.h"
#include <ros/ros.h>
#include <sp_common/DbusData.h>
#include <sp_common/SingleJointWrite.h>
#include <sp_common/GpioData.h>

#define chassis_x_coeff 2.0
#define chassis_y_coeff 2.0
#define chassis_z_coeff_kb 70
#define chassis_z_coeff_rc 1.5
#define gimbal_x_coeff 0.03
#define gimbal_y_coeff_kb 2
#define gimbal_y_coeff_rc 0.07
#define gimbal_z_coeff 0.002
#define joint_coeff 0.05
class DBusNode
{
private:
  ros::NodeHandle nh_;
  ros::Publisher dbus_pub_;
  ros::Publisher cmd_vel_pub_;
  ros::Publisher cmd_pos_pub_;
  ros::Publisher gpio_pub_;
  ros::Subscriber gpio_sub_;
  std::string serial_port_;
  sp_common::DbusData dbus_cmd_;
  geometry_msgs::Twist cmd_vel_;
  geometry_msgs::Vector3 cmd_pos_;
  bool gripper_signal, sucker_signal, rob_signal;
  bool last_q, last_w, last_e;
  DBus dbus_{};
  sp_common::GpioData gpio_data;

public:
  DBusNode();
  ~DBusNode() = default;
  void run();
  bool is_update() { return dbus_.get_update(); }
  void gpio_callback(const sp_common::GpioData::ConstPtr &gpio_data_);
};
#endif // SRC_RM_BRIDGE_INCLUDE_DBUS_NODE_H_
