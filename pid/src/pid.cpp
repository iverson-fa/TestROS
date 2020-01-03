/*
    dafa 20191224.1818
*/

#include "ros/ros.h"
#include <iostream>
#include <std_msgs/String.h>
#include <pid/VehicleInfo.h>
#include <pid/VehicleCmd.h>
#include <pid/Gear.h>
#include <pid/VehicleOtherCmd.h>
#include <pid/DecisionCmd.h>
#include <pid/VirtualWall.h>
#include <pid/GNSSInfo.h>
#include <pid/PlanningCmd.h>
#include <pid/WayPoint.h>
#include <pid/TruckState.h>
#include <pid/VehicleState.h>
#include <pid/VehicleCmdDebug.h>
#include <pid/ForceVehicleCmd.h>
#include <pid/VehicleOtherInfo.h>




class Controller
{
public:
    ros::NodeHandle nh;
    ros::Publisher  vehicle_cmd_pub_ ;
    ros::Subscriber vehicle_info_sub_;
    ros::Subscriber sub;
    pid::VehicleInfo vehicle_info_;
    pid::VehicleCmd vehicle_cmd_;
    pid::VehicleCmd vehicle_step_cmd_;
    double current;
    double dest;
public:
    Controller();
    ~Controller();
    void vehicleInfoCallback(const pid::VehicleInfo::ConstPtr& vehicle_info);
    void chatterCallback(const std_msgs::String::ConstPtr& msg);
};

Controller::Controller()
{
    vehicle_cmd_pub_  = nh.advertise<pid::VehicleCmd>("/pnc_msgs/vehicle_cmd",1);
    vehicle_info_sub_ = nh.subscribe("/pnc_msgs/vehicle_info", 10, &Controller::vehicleInfoCallback, this);
    sub = nh.subscribe("chatter", 1000, &Controller::chatterCallback, this);
    current = 0.0;
    dest = 5.0;
}

Controller::~Controller()
{
    /*
    if(nh){
        delete(nh);
    }
    */
}


void Controller::chatterCallback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("I heard :[%s].",msg->data.c_str());
}

void Controller::vehicleInfoCallback(const pid::VehicleInfo::ConstPtr& vehicle_info){
    ROS_INFO("I heard :pid.");

    vehicle_cmd_.steering_mode = pid::VehicleCmd::MODE_AUTO;
    vehicle_cmd_.throttle_mode = pid::VehicleCmd::MODE_AUTO;
    vehicle_cmd_.brake_mode = pid::VehicleCmd::MODE_AUTO;
    vehicle_cmd_.gear_mode = pid::VehicleCmd::MODE_AUTO;

    vehicle_step_cmd_.steering_mode = pid::VehicleCmd::MODE_AUTO;
    vehicle_step_cmd_.throttle_mode = pid::VehicleCmd::MODE_AUTO;
    vehicle_step_cmd_.brake_mode = pid::VehicleCmd::MODE_AUTO;
    vehicle_step_cmd_.gear_mode = pid::VehicleCmd::MODE_AUTO;
    ROS_INFO("test cmd 01");


    vehicle_cmd_.steering_angle = 0.0;
    vehicle_cmd_.brake = 0.10;
    vehicle_cmd_.throttle = 0.0;
    vehicle_cmd_.header.stamp = ros::Time::now();
    vehicle_cmd_.acceleration_mode = 101;
    ROS_INFO("test cmd 02");

    vehicle_info_ = *vehicle_info;
    current = vehicle_info_.vehicle_speed;
    ROS_INFO("current %f", current);

    if(current = dest){
        vehicle_cmd_.throttle = 0;
        vehicle_cmd_.brake = 0;
        vehicle_cmd_.gear.value = 2;
    }
    else if(current < dest){
        vehicle_cmd_.throttle = 0.002;
        vehicle_cmd_.brake = 0;
        vehicle_cmd_.gear.value = 2;

    }
    else{
        vehicle_cmd_.steering_angle = 0.0;
        vehicle_cmd_.brake = 0.20;
        vehicle_cmd_.throttle = 0.0;
    }

    vehicle_cmd_pub_.publish(vehicle_cmd_);
    ROS_INFO("test cmd 03");

}








int main(int argc,char **argv)
{
    ros::init(argc,argv,"control_strategy_node");

    Controller change;

    ros::spin();

    return 0;
}
