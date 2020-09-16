#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/Odometry.h>

void counterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  ROS_INFO("%lf", msg->pose.pose.position.x);
  ROS_INFO("%lf", msg->pose.pose.position.y);
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "topic_subscriber");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("/odom", 1000, counterCallback);
    
    ros::spin();
    
    return 0;
}