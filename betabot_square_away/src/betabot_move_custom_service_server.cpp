#define _USE_MATH_DEFINES
#include <cmath>
#include "ros/ros.h"
#include "betabot_square_away/BetabotCustomServiceMessage.h"
#include <geometry_msgs/Twist.h>
#include "nav_msgs/Odometry.h"
#include <time.h>

// define vars members of struct
// struct beta_pos {
//     double x;         // x location 
//     double y;         // y location 
// };

// class to hold our methods
class BetabotSquare{
    public:
        ros::Publisher vel_pub;

        bool full_square(betabot_square_away::BetabotCustomServiceMessage::Request  &req,
          betabot_square_away::BetabotCustomServiceMessage::Response &res){
          std::cout <<"Handling move " << std::endl; 
          int counter = 0;
          while (counter != req.repetitions){
                move(req,1);
                rotate();
                move(req,2);
                rotate();
                move(req,1);
                rotate();
                move(req,2);
                counter+=1;
            };
            std::cout <<"Spongebob Squarepants" <<std::endl;
            res.success = true;  
            return res.success;
        }
            
        void OdomCallback(const nav_msgs::OdometryConstPtr &msg){
            x_ = msg->pose.pose.position.x;  // get the robot x pose from the odom topic
            y_ = msg->pose.pose.position.y;  // get the robot y pose from the odom topic
            angle = ToAngles(msg->pose.pose.orientation);
            }

    private:
        double x_;
        double y_;
        double angle;

        bool rotate(){
            
            double speed = 50;

            geometry_msgs::Twist vel_msg;
            double angular_speed = speed*2*M_PI/360;

            vel_msg.linear.x = 0; //random vel
            //Since we are moving just in x-axis
            vel_msg.linear.y = 0;
            vel_msg.linear.z = 0;
            vel_msg.angular.x = 0;
            vel_msg.angular.y = 0;
            vel_msg.angular.z = angular_speed;
            double init_angle = angle;
            double angle_moved = 0;
            // if(init_angle < 0){
            //     init_angle = init_angle + 2*M_PI;
            // }
            std::cout << "init angle: " << init_angle+M_PI <<std::endl;
            while(ros::ok()){
                    //Loop to move the turtle in an specified distance
                    vel_pub.publish(vel_msg);
                    // angle + 2*M_PI so that I dont deal with negatives
                    do{
                        ros::spinOnce();
                        angle_moved  += angle -init_angle; 
                        if (angle_moved > M_PI)
                            angle_moved -= 2 * M_PI;
                        else if (angle_moved <  - M_PI)
                            angle_moved += 2 * M_PI;      
                        std::cout << "angle moved: " << angle_moved <<std::endl;               
                        init_angle = angle;
                    }while(angle_moved < M_PI_2 - 0.012);

                    std::cout << "current angle: " << angle <<std::endl; 

                    //After the loop, stops the robot
                    vel_msg.linear.z = 0;
                    vel_pub.publish(vel_msg);
                    std::cout <<"angle done" <<std::endl; 
                    return true;
            };
         }
        bool move(betabot_square_away::BetabotCustomServiceMessage::Request  &req,
                    int dir)
        {
            double speed = 0.5;
            geometry_msgs::Twist vel_msg;

            vel_msg.linear.x = speed; //random vel
            vel_msg.linear.y = 0;
            //Since we are moving just in x-axis
            vel_msg.linear.z = 0;
            vel_msg.angular.x = 0;
            vel_msg.angular.y = 0;
            vel_msg.angular.z = 0;

            while(ros::ok()){
                    //Loop to move the turtle in an specified distance
                    double init_pos_x = x_;
                    double init_pos_y = y_;
                    vel_pub.publish(vel_msg);
                    while(dist(x_-init_pos_x,y_-init_pos_y) < req.side){
                    //Publish the velocity   
                    ros::spinOnce();
                    };
                    //After the loop, stops the robot
                    vel_msg.linear.x = 0;
                    vel_pub.publish(vel_msg);

                    std::cout <<"Inital Position: x = "<< init_pos_x <<" y = " << init_pos_y <<std::endl; 
                    std::cout <<" Position: x = "<< x_ <<" y = " << y_ <<std::endl; 
                    std::cout <<"side done" <<std::endl; 
                    return true;
            };
        }  
        double dist(double x, double y){
                return sqrt(std::pow(x,2)+std::pow(y,2));
        };
        double ToAngles(geometry_msgs::Quaternion q) {

        double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
        double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
        double yaw = std::atan2(siny_cosp, cosy_cosp);

        return yaw;
        }
};


int main(int argc, char **argv)                // Node Main Function
{
  ros::init(argc, argv, "move_server");   // Initializes Node Name
  ros::NodeHandle nh;                          // Node handle declaration

  // Create instance form our class
  //LandMarkMonitor monitor;
  BetabotSquare square; 
  // Hook our service Servers to the master
  ros::ServiceServer service = nh.advertiseService("move",&BetabotSquare::full_square, &square);
 
  ROS_INFO("Ready to start moving the robot");
  // Hook our Subscriber to the master
  square.vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  ros::Subscriber sub = nh.subscribe("/odom",0 ,&BetabotSquare::OdomCallback, &square);
  ros::spin();                                 // Wait for ever for the service request

  return 0;
}