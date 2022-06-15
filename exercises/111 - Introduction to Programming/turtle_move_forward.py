#! usr#!/usr/bin/env python

import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

    
def shutdown():
    # stop turtlebot
    rospy.loginfo("Stop TurtleBot")
    # a default Twist has linear.x of 0 and angular.z of 0.  So it'll stop TurtleBot
    pub.publish(Twist())
    # sleep just makes sure TurtleBot receives the stop command prior to shutting down the script
    rospy.sleep(1)




rospy.init_node('move_forward')                          		#Initiate node
rospy.loginfo("To stop TurtleBot CTRL + C")
rospy.on_shutdown(shutdown)                              		#Specifies what the turtlebot should do once Ctrl+C is pressed
pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)                 #Specify where to publish commands for turtlebot
move = Twist()                                           		#Twist is the datatype for velocity
r = rospy.Rate(10)					 		#Means commands should be sent at a rate of 10 Hz




move.linear.x = 0.3                         #Set linear x velocity to 0.3 m/s
move.angular.z = 0.0                        #Set angular velocity to 0 m/s
print('Moving forward')


while not rospy.is_shutdown():
	pub.publish(move)                           #Send the command to the turtlebot
	r.sleep()				    #Controls the frequency of the commands being sent to the robot

