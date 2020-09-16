#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
float right = 0;
float middle = 0;
float left = 0;
void counterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  right = msg->ranges[0];
  middle = msg->ranges[360];
  left = msg->ranges[719];
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "topics_quiz_node");
    ros::NodeHandle nh;
    
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    ros::Subscriber sub = nh.subscribe("/kobuki/laser/scan", 1000, counterCallback);
    ros::Rate loop_rate(2);
    
    geometry_msgs::Twist var;
    
    while (ros::ok())
    {
        if (middle > 1) {
            var.linear.x = 0.3;
            var.angular.z = 0;
            pub.publish(var);
        }
        else if (middle < 1) {
            var.linear.x = 0;
            var.angular.z = 0.3;
            pub.publish(var);
        }
        else if (right < 1) {
            var.linear.x = 0;
            var.angular.z = 0.3;
            pub.publish(var);
        }
        else if (left < 1) {
            var.linear.x = 0;
            var.angular.z = -0.3;
            pub.publish(var);
        }
        else {
            var.linear.x = 0.3;
            var.angular.z = 0;
            pub.publish(var);
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
    pub.publish(var);
    return 0;
}