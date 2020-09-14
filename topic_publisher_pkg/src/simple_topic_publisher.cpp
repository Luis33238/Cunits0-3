#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv) {

    ros::init(argc, argv, "topic_publisher");
    ros::NodeHandle nh;
    
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    ros::Rate loop_rate(2);
    
    geometry_msgs::Twist var;
    var.linear.x = 0.5;
    var.angular.z = 0.5;
    
    while (ros::ok())
    {
        pub.publish(var);
        ros::spinOnce();
        loop_rate.sleep();
    }
    var.linear.x = 0;
    var.angular.z = 0;
    pub.publish(var);
    return 0;
}