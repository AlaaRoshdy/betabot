#!/usr/bin/env python

import rospy
import math
import random as rand

from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Float32

range_front = Float32()
range_left = Float32()
range_right = Float32()
#Initial values

normal_vel =0.5
max_angle = 1.57284
min_angle = -max_angle

def callback(msg):
	# rospy.loginfo("MAX LEN %f",len(msg.ranges))
	range_right.data= min(min(msg.ranges[0:999]), 10)
	# range_front.data= min(min(msg.ranges[666:1332]), 10)
	range_left.data= min(min(msg.ranges[1000:1999]), 10)


def move():
	# Initialize node
	rospy.init_node('laser')
	pub = rospy.Publisher('cmd_vel', Twist, queue_size=5)
	sub = rospy.Subscriber("scan", LaserScan, callback)
	rate = rospy.Rate(10) # 10hz
	twist = Twist()
	# Move the robot
	while not rospy.is_shutdown():
		rospy.loginfo("VALUE LEFT %f",range_left.data)
		# rospy.loginfo("VALUE FRONT %f", range_front.data)
		rospy.loginfo("VALUE RIGHT %f", range_right.data)
		if (range_right.data >0.5):
			twist.linear.x = normal_vel; twist.linear.y = normal_vel; twist.linear.z = 0
			twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0
			pub.publish(twist)
			rospy.loginfo("Moving right with speed %f", normal_vel)

		else:
			if (range_left.data>0.5):
				twist.linear.x = normal_vel; twist.linear.y = -normal_vel; twist.linear.z = 0
				twist.angular.x = 0; twist.angular.y = 0; twist.angular.z =  normal_vel
				pub.publish(twist)
				rospy.loginfo("Obstacle on my right! moving left %f", -normal_vel)
			else:
				twist.linear.x =0; twist.linear.y = 0; twist.linear.z = 0
				twist.angular.x = 0; twist.angular.y = 0; twist.angular.z =  normal_vel
				pub.publish(twist)
				rospy.loginfo("Obstacle at my left! rotating right %f", twist.angular.z)
		rate.sleep()
		

if __name__ == '__main__':
    try:
        move()
    except rospy.ROSInterruptException:
        pass


