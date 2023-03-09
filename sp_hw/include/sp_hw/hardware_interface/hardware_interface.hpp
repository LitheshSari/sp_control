#pragma once

#include <unordered_map>

#include <ros/ros.h>
#include <urdf/model.h>
#include <XmlRpcValue.h>

/* ROS Control */
#include <hardware_interface/robot_hw.h>

#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/actuator_state_interface.h>
#include <hardware_interface/actuator_command_interface.h>

#include <transmission_interface/transmission_interface_loader.h>

/* SP HW */
#include "sp_hw/hardware_interface/data_types.hpp"
#include "sp_hw/hardware_interface/can_bus.hpp"

/* publish ActuatorState */
#include <realtime_tools/realtime_publisher.h>
#include <sp_common/hardware_interface/gpio_interface.h>
#include "sp_common/ActuatorState.h"
#include "sp_common/GpioData.h"


namespace sp_hw
{
    class SpRobotHW : public hardware_interface::RobotHW
    {
    public:
        SpRobotHW() = default;
        void setCanBusThreadPriority(const int &thread_priority);
        bool init(ros::NodeHandle &root_nh, ros::NodeHandle &robot_hw_nh) override;
        void read(const ros::Time &time, const ros::Duration &period);
        void write(const ros::Time &time, const ros::Duration &period);

        void publishActuatorState(const ros::Time &time);

    private:
        bool is_actuator_specified_, is_gpio_specified_= false;
         
        int thread_priority_ = 0;
        // Param Parse
        bool parseActCoeffs(XmlRpc::XmlRpcValue &act_coeffs);
        bool parseActData(XmlRpc::XmlRpcValue &act_data);
        bool parseGpioData(XmlRpc::XmlRpcValue &gpio_datas);
        bool initCanBus(XmlRpc::XmlRpcValue &can_bus);
        bool loadUrdf(ros::NodeHandle &root_nh);
        bool setupTransmission(ros::NodeHandle &root_nh);

        // CanBus used as the actuator communication interface
        std::vector<std::unique_ptr<CanBus>> can_buses_;
        // URDF model of the robot
        std::string urdf_string_;
        std::shared_ptr<urdf::Model> urdf_model_;
        //Gpio
        sp_control::GpioStateInterface gpio_state_interface_;
        sp_control::GpioCommandInterface gpio_command_interface_;

        // joint_handle
        std::vector<hardware_interface::JointHandle> effort_joint_handles_;
        // ActuatorParam & Actuator Interface
        std::unordered_map<std::string, ActCoeff> type2act_coeffs_;
        std::unordered_map<std::string, std::unordered_map<int, ActData>> bus_id2act_data_;
        std::unordered_map<std::string, std::unordered_map<int, sp_control::GpioData>> bus_id2gpio_data_;
        hardware_interface::ActuatorStateInterface act_state_interface_;
        hardware_interface::EffortActuatorInterface effort_act_interface_;
        // Transmission
        std::unique_ptr<transmission_interface::TransmissionInterfaceLoader> transmission_iface_loader_;
        transmission_interface::RobotTransmissions robot_transmissions_;
        transmission_interface::ActuatorToJointStateInterface *act_to_jnt_state_;
        transmission_interface::JointToActuatorEffortInterface *jnt_to_act_effort_;

        // ActuatorState Publisher
        ros::Time last_publish_time_;
        std::unique_ptr<realtime_tools::RealtimePublisher<sp_common::ActuatorState>> actuator_state_pub_;
    };
} // namespace : sp_hw
