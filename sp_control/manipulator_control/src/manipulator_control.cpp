#include "manipulator_control/arm_control.h"
#include "manipulator_control/scene_generate.h"
#include <std_msgs/Float64MultiArray.h>
#include "sp_common/SingleJointWrite.h"
#include "sp_common/DbusData.h"

void pose_callback(const geometry_msgs::Pose::ConstPtr &pose_, manipulator_control::Manipulator *manipulator)
{
    manipulator->write(*pose_);
}

void state_callback(const std_msgs::Float64MultiArray::ConstPtr &state_, manipulator_control::Manipulator *manipulator)
{
    std::vector<double> state;
    state = state_->data;
    manipulator->write(state);
}

void single_state_callback(const sp_common::SingleJointWrite::ConstPtr &state_, manipulator_control::Manipulator *manipulator)
{
    double state;
    int num;
    state = state_->state;
    num = state_->num;
    manipulator->singlewrite(state, num);
}

void remote_control_callback(const sp_common::DbusData::ConstPtr &data_, sp_common::DbusData *dbusdata_)
{

    *dbusdata_ = *data_;
}

void ore_pose_callback(const geometry_msgs::Pose::ConstPtr &pose_, geometry_msgs::Pose *pose)
{
    *pose = *pose_;
}

bool pose_check(geometry_msgs::Pose pose)
{
    if (pose.position.y > 0 && pose.position.y < 0.7 && pose.position.z > 0 && pose.position.z < 0.8)
        return true;
    else
        return false;
}



int main(int argc, char **argv)
{

    ros::init(argc, argv, "trajectory_control", ros::init_options::AnonymousName);
    ros::AsyncSpinner spinner(3);
    moveit::planning_interface::MoveGroupInterface move_group_interface(PLANNING_GROUP_MANIPULATOR);
    //moveit::planning_interface::MoveGroupInterface grip_group_interface(PLANNING_GROUP_GRIPPER);
    manipulator_control::Manipulator manipulator_(move_group_interface);
    manipulator_control::Scene scene;
    scene.init();
    std::string ore_id = "golden_ore";
    std::string sink_id = "exchange_sink";
    geometry_msgs::Pose ore_pose;
    sp_common::DbusData dbusdata_;
    shapes::Mesh *ore = shapes::createMeshFromResource("package://sp_description/meshes/scene/gloden_ore.STL");
    shapes::Mesh *sink = shapes::createMeshFromResource("package://sp_description/meshes/scene/exchange_sink.STL");
    ros::NodeHandle nh;
    ros::Subscriber pose_sub = nh.subscribe<geometry_msgs::Pose>("/moveit/pose_sub", 10, boost::bind(&pose_callback, _1, &manipulator_));
    ros::Subscriber state_sub = nh.subscribe<std_msgs::Float64MultiArray>("/moveit/state_sub", 10, boost::bind(&state_callback, _1, &manipulator_));
    ros::Subscriber single_sub = nh.subscribe<sp_common::SingleJointWrite>("/moveit/single_state_sub", 10, boost::bind(&single_state_callback, _1, &manipulator_));
    ros::Subscriber remote_control_sub = nh.subscribe<sp_common::DbusData>("dbus_data", 10, boost::bind(&remote_control_callback, _1, &dbusdata_));
    ros::Subscriber ore_pose_sub = nh.subscribe<geometry_msgs::Pose>("ore_detect_pose", 10, boost::bind(&ore_pose_callback, _1, &ore_pose));
    spinner.start();
    moveit_msgs::AttachedCollisionObject ore_ = scene.generate_attach_collision_obj(ore_id, ore);
    geometry_msgs::Pose pose;
    pose.position.x = 0.0;
    pose.position.y = -0.2;
    pose.position.z = 0.6;
    pose.orientation.w = 0.0;
    pose.orientation.x = 0.0;
    pose.orientation.y = 1.0;
    pose.orientation.z = 0.0;
    if (manipulator_.init())
    {
        
       

        while (ros::ok())
        {
            manipulator_.read();
            manipulator_.write(pose);
            
         
            if (dbusdata_.s_l == 3 && dbusdata_.s_r == 2) // enter the fine turing modd
            {
                if (dbusdata_.key_shift)  
                {
                    if (dbusdata_.key_a)
                    {
                        ROS_INFO_STREAM("JOINT1!!!  ");
                        manipulator_.singleaddwrite(joint_eff_large, 1);
                    }
                        
                    else if (dbusdata_.key_z)
                        manipulator_.singleaddwrite(-joint_eff_large, 1);
                    if (dbusdata_.key_s)
                    {
                        ROS_INFO_STREAM("JOINT2!!!  ");
                        manipulator_.singleaddwrite(joint_eff_large, 2);
                    }
                    else if (dbusdata_.key_x)
                        manipulator_.singleaddwrite(-joint_eff_large, 2);
                    if (dbusdata_.key_d)
                    {
                        ROS_INFO_STREAM("JOINT3!!!  ");
                        manipulator_.singleaddwrite(joint_eff_large, 3);
                    }
                    else if (dbusdata_.key_c)
                        manipulator_.singleaddwrite(-joint_eff_large, 3);
                } 
                else
                {
                    if (dbusdata_.key_a)
                    {
                        ROS_INFO_STREAM("JOINT4!!!  ");
                        manipulator_.singleaddwrite(joint_eff_small, 4);
                    }
                    else if (dbusdata_.key_z)
                        manipulator_.singleaddwrite(-joint_eff_small, 4);
                    if (dbusdata_.key_s)
                    {    
                        ROS_INFO_STREAM("JOINT5!!!  ");
                        manipulator_.singleaddwrite(joint_eff_small, 5);
                    }
                        
                    else if (dbusdata_.key_x)
                        manipulator_.singleaddwrite(-joint_eff_small, 5);
                    if (dbusdata_.key_d)
                    {
                        ROS_INFO_STREAM("JOINT6!!!  ");
                        manipulator_.singleaddwrite(joint_eff_small, 6);
                    }
                        
                    else if (dbusdata_.key_c)
                        manipulator_.singleaddwrite(-joint_eff_small, 6);

                }             


                if (dbusdata_.key_r) // go home
                {
                   manipulator_.goal("home");    
                }
                else if (dbusdata_.key_f)
                {
                    manipulator_.goal("left_up");   
                }
                else if (dbusdata_.key_v)
                {
                    manipulator_.goal("forward");       
                }
                 else if (dbusdata_.key_g)
                {
                    manipulator_.goal("exchange");       
                }
                
               //if (dbusdata_.key_g) 
               // {
               //     auto_take_silver_ore(&manipulator_, ore_pose);
               // } 
                //else if (dbusdata_.key_b) 
                //{
                    //auto_exchange(&manipulator_);
                //} 
             }
            //   }

            // else if () // go forward grip

            // else if () // go left grip205083

            // else if () // go

            // if ()
            // auto_take_silver_ore(*manipulator_, target_pose);
            // manipulator_.read();
            // manipulator_.goal("grip");
            // manipulator_.move_execute();
            // manipulator_.suck(true);
            // sleep(3);
            // manipulator_.suck(false);
            // sleep(3);

            // if (manipulator_.get_executed() == false)
            //{
            //     manipulator_.move_execute();
            //     manipulator_.set_executed(true);
            //}
            // loop_rate.sleep();

            ros::spinOnce();
        }
    }
    return 0;
}


/*
int main(int argc, char **argv)
{
 ros::init(argc, argv, "trajectory_control");
 ros::NodeHandle nh;
 ros::AsyncSpinner spin(1);
 spin.start();

 // 创建运动规划的情景，等待创建完成
 moveit::planning_interface::PlanningSceneInterface current_scene;

 // 声明一个障碍物的实例，并且为其设置一个id，方便对其进行操作，该实例会发布到当前的情景实例中
 moveit_msgs::CollisionObject cylinder;
 cylinder.id = "seven_dof_arm_cylinder";

 // 设置障碍物的外形、尺寸等属性
 shape_msgs::SolidPrimitive primitive;
 primitive.type = primitive.CYLINDER;
 primitive.dimensions.resize(3);
 primitive.dimensions[0] = 0.6;
 primitive.dimensions[1] = 0.2;

 // 设置障碍物的位置
 geometry_msgs::Pose pose;
 pose.orientation.w = 1.0;
 pose.position.x =  1.0;
 pose.position.y = -1.4;
 pose.position.z =  1.4;

 // 将障碍物的属性、位置加入到障碍物的实例中
 cylinder.primitives.push_back(primitive);
 cylinder.primitive_poses.push_back(pose);
 cylinder.operation = cylinder.ADD;

 // 创建一个障碍物的列表，把之前创建的障碍物实例加入其中
 std::vector<moveit_msgs::CollisionObject> collision_objects;
 collision_objects.push_back(cylinder);

 // 所有障碍物加入列表后（这里只有一个障碍物），再把障碍物加入到当前的情景中，如果要删除障碍物，使用removeCollisionObjects(collision_objects)
 current_scene.addCollisionObjects(collision_objects);

 ros::shutdown();

 return 0;
}*/
