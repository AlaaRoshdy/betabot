
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>

class ObstacleAvoider{

public:
	ros::Publisher vel_pub;

	void Callback(const sensor_msgs::LaserScan::ConstPtr& msg)
	{
		geometry_msgs::Twist cmdvel;
	// printf("Position: [%f] [%f]\n", msg->range_min,msg->range_max);
		min_dist=msg->ranges[0];
		min_angle=0;
		//Min angle is 0, max is 2 pi
		for(int j=0;j<=1999;j++)
			{
				if(msg->ranges[j]<min_dist)
				{
					min_dist=msg->ranges[j];
					min_angle=j*2*M_PI/2000;
				}
			}
			// printf("max angle is %f  and  min angle is %f", msg->angle_max, msg->angle_min);
			printf("minimum distance is [%f] at an angle of [%f]\n",min_dist,min_angle);
		if(min_dist<=1.0)  // min_dist<=0.5 gave box pushing like behaviour, min_dist<=1.2 gave obstacle avoidance
		{
			if(min_angle<90)
			{
				cmdvel.angular.z=1.0;
				cmdvel.linear.x=0;
				
				cmdvel.linear.y=0;
				cmdvel.linear.z=0;
				cmdvel.angular.x=0;
				cmdvel.angular.y=0;
				printf("left\n");
			}
			else
			{
				cmdvel.angular.z=-1.0;
				cmdvel.linear.x=0;

				cmdvel.linear.y=0;
				cmdvel.linear.z=0;
				cmdvel.angular.x=0;
				cmdvel.angular.y=0;
				printf("right\n");
			}
		}
		else
		{
			cmdvel.linear.x=1.0;
			cmdvel.angular.z=0;
			printf("straight\n");
		}
		
		vel_pub.publish(cmdvel);

	}
	private:
	float min_dist;
	float min_angle;

};

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "laser");
  ros::NodeHandle nh;

  ObstacleAvoider avoider;

  avoider.vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
  ros::Subscriber sub = nh.subscribe("scan", 1, &ObstacleAvoider::Callback, &avoider);

  ros::spin();

  return 0;
}