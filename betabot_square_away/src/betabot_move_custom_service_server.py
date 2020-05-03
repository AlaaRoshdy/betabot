#!/usr/bin/env python

from move_betabot_in_square_custom.srv import *
from geometry_msgs.msg import Twist
import rospy

def handle_move(req):
    print "handling move"
    # move it
    speed = 0.5
    vel_msg = Twist()
    vel_msg.linear.x = speed #random vel
    velocity_publisher = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    #Since we are moving just in x-axis
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0

    while not rospy.is_shutdown():
        counter = 0
        while (counter != req.repetitions):
            #Loop to move the turtle in an specified distance
            #Setting the current time for distance calculus
            t0 = rospy.Time.now().to_sec()
            current_distance = 0
            while(current_distance < req.side):
                #Publish the velocity   
                velocity_publisher.publish(vel_msg)
                #Takes actual time to velocity calculus
                
                t1=rospy.Time.now().to_sec()
                #Calculates distancePoseStamped
                current_distance= speed*(t1-t0)
            print current_distance
            #Force the robot to stop
            counter+=1
            print "first side done"
        #After the loop, stops the robot
        vel_msg.linear.x = 0
        velocity_publisher.publish(vel_msg)
        print "done"
        return True


def betabot_move_custom_service_server():
    rospy.init_node('move_server')
    s = rospy.Service('/move', BetabotCustomServiceMessage, handle_move)
    print "Ready to start moving the robot"
    rospy.spin()

if __name__ == "__main__":
    betabot_move_custom_service_server()