#! /usr/bin/env python

print "move_robot"

#! /usr/bin/env python
import rospy
from sensor_msgs.msg import JointState
from nav_msgs.msg import Odometry
from std_msgs.msg import String 
from geometry_msgs.msg import Twist
import numpy as np
import time as t
import math

## Global Frame Velocities 
## Initial conditions
x0 = 0.0 # x (m)
y0 = 0.0 # y (m)
t0 = 0.0 # theta (rad)


tt0 = None
def callback(msg): 
    print msg.data
    d = msg.data
    tw = Twist()

    if (d == "one"):
        tw.linear.x = 0.5 
        tw.angular.z = 0.5
        pub.publish(tw)
        t.sleep(7)
        tw.angular.z = -0.5
        pub.publish(tw)
        t.sleep(7)
        tw.angular.z = 0.5
        pub.publish(tw)
        t.sleep(7)
        tw.angular.z = -0.5
        pub.publish(tw)
        t.sleep(7)
        tw.linear.x = 0
        tw.angular.z = 0
        pub.publish(tw)
    elif (d == "two"):
        tw.linear.x = 0.5 
        tw.angular.z = 1
        pub.publish(tw)
        t.sleep(3.5)
        tw.angular.z = -1
        pub.publish(tw)
        t.sleep(3.5)
        tw.angular.z = 1
        pub.publish(tw)
        t.sleep(3.5)
        tw.angular.z = -1
        pub.publish(tw)
        t.sleep(3.5)
        tw.linear.x = 0
        tw.angular.z = 0
        pub.publish(tw)
    elif (d == "stop"):
        tw.linear.x = 0
        tw.angular.z = 0
    elif (d == "three"):
        tw.linear.x = 0.5 
        tw.angular.z = 1.5
        pub.publish(tw)
        t.sleep(2.3333333)
        tw.angular.z = -1.5
        pub.publish(tw)
        t.sleep(2.3333333)
        tw.angular.z = 1.5
        pub.publish(tw)
        t.sleep(2.33333333)
        tw.angular.z = -1.5
        pub.publish(tw)
        t.sleep(2.33333333)
        tw.linear.x = 0
        tw.angular.z = 0
        pub.publish(tw)
    elif (d == "test"):
        tw.angular.z = 1.5
        pub.publish(tw)
        t.sleep(2.3333333)
        while (d == "test"):
            time = t.time()
            tw.linear.x = abs(math.cos(time))
            tw.angular.z = math.sin(time)
            pub.publish(tw)
    else:
        tw.angular.z = 1.5
        pub.publish(tw)
        t.sleep(2.3333333)
        while (x0 == 0.0):
            time = t.time()
            tw.linear.x = abs(int(d)*math.cos(int(d)*time))
            tw.angular.z = math.sin(int(d)*time)
            pub.publish(tw)
    pub.publish(tw)

rospy.init_node('move_robot')
sub = rospy.Subscriber('/key_press', String, callback)
pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)


rospy.spin()