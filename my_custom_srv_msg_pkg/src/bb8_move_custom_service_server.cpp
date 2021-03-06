#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include <geometry_msgs/Twist.h>
#include <my_custom_srv_msg_pkg::MyCustomServiceMessage.h>
// Import the service message header file generated from the Empty.srv message
float forward = 0;
float turning = 0;
float duration = 0;
// We define the callback function of the service
bool my_callback(my_custom_srv_msg_pkg::MyCustomServiceMessage::Request  &req,
                 my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res)
{ 
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ROS_INFO("Enter duration: %i", req.duration);
  forward = 0.5;
  turning = 0.5;
  geometry_msgs::Twist var;
  var.linear.x = forward;
  var.angular.z = turning;
  duration = req.duration;
  pub.publish(var);
  sleep(duration);
  res.success = true;
  ROS_INFO("My_callback has been called"); // We print an string whenever the Service gets called
  return res.success;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;

  ros::ServiceServer move_bb8_in_circle_custom = nh.advertiseService("/move_bb8_in_square_custom", my_callback); // create the Service called                                                                                          // my_service with the defined                                                                                        // callback
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  geometry_msgs::Twist var;
  var.linear.x = forward;
  var.angular.z = turning;
  pub.publish(var);
  sleep(duration);
  var.linear.x = 0;
  var.angular.z = 0;
  pub.publish(var);
  ros::spin(); // mantain the service open.

  return 0;
}