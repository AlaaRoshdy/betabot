#!/usr/bin/env python

from move_betabot_in_square_custom.srv import *
import rospy
import sys
from geometry_msgs.msg import Twist


# Wait for service client /gazebo/* to be running
def move_client(side, repetitions):
    rospy.wait_for_service('/move')
    try:
            move = rospy.ServiceProxy('/move', BetabotCustomServiceMessage)
            resp1 = move(side, repetitions)
            return resp1.success

    except rospy.ServiceException:
            print "Service call failed"

def usage():
    return "%s [side repetitions]"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 3:
        side = float(sys.argv[1])
        repetitions = int(sys.argv[2])
    else:
        print usage()
        sys.exit(1)
    print "Requesting movement"
    print "Successful?? %s"%(move_client(side,repetitions))
    
