#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include <geometry_msgs/Twist.h>
// Import the service message header file generated from the Empty.srv message
float forward = 0;
float turning = 0;
// We define the callback function of the service
bool my_callback(std_srvs::Empty::Request  &req,
                 std_srvs::Empty::Response &res)
{ 
  ros::NodeHandle nh;
  forward = 0.5;
  turning = 0.5;
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  geometry_msgs::Twist var;
  var.linear.x = 0.5;
  var.angular.z = 0.5;
  pub.publish(var);
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO("My_callback has been called"); // We print an string whenever the Service gets called
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;

  ros::ServiceServer move_bb8_in_circle = nh.advertiseService("/move_bb8_in_circle", my_callback); // create the Service called                                                                                          // my_service with the defined                                                                                        // callback
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  geometry_msgs::Twist var;
  var.linear.x = forward;
  var.angular.z = turning;
  pub.publish(var);
  ros::spin(); // mantain the service open.

  return 0;
}