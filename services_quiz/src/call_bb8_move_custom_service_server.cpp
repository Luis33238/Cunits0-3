#include "ros/ros.h"
#include <ros/package.h>
#include <services_quiz::BB8CustomServiceMessage.h>
// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_client"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;
  // Create the connection to the service /trajectory_by_name
  ros::ServiceClient traj_by_name_service = nh.serviceClient<services_quiz::BB8CustomServiceMessage>("/move_bb8_in_square_custom");
  services_quiz::BB8CustomServiceMessage srv; // Create an object of type TrajByName
  srv.request.side = 2;
  srv.request.repetitions = 2;
  if (traj_by_name_service.call(srv)) // Send through the connection the name of the trajectory to execute
  {
  }
  else
  {
    ROS_ERROR("Failed to call service /trajectory_by_name");
    return 1;
  }
  srv.request.side = 5;
  srv.request.repetitions = 1;
  if (traj_by_name_service.call(srv)) // Send through the connection the name of the trajectory to execute
  {
  }
  else
  {
    ROS_ERROR("Failed to call service /trajectory_by_name");
    return 1;
  }
  return 0;
}