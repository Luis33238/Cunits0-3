#include "ros/ros.h"
#include "iri_wam_reproduce_trajectory/ExecTraj.h"
#include <ros/package.h>
// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_client"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;
  // Create the connection to the service /trajectory_by_name
  ros::ServiceClient traj_by_name_service = nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>("/execute_trajectory");
  iri_wam_reproduce_trajectory::ExecTraj srv; // Create an object of type TrajByName
  srv.request.file = ros::package::getPath("iri_wam_reproduce_trajectory") + "/config/get_food.txt";
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