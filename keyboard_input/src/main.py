#! /usr/bin/env python

print "keyboard"

import rospy
from std_msgs.msg import String 
import numpy as np

rospy.init_node('keypress')
pub = rospy.Publisher('/key_press', String, queue_size=1)


while(True):
    val = raw_input("Input Frequency: ")
    print(val)
    pub.publish(val)