#include "ros/ros.h"
#include "betabot_square_away/BetabotCustomServiceMessage.h"
#include <cstdlib>

int main(int argc, char **argv)                // Node Main Function
{
  ros::init(argc, argv, "move_client");   // Initializes Node Name
  if(argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }
  ros::NodeHandle nh;                          // Node handle declaration

  // Hook our service clients to the master
  ros::ServiceClient client = nh.serviceClient<betabot_square_away::BetabotCustomServiceMessage>("move");
  
  // create request and response 
  betabot_square_away::BetabotCustomServiceMessage srv;

  srv.request.side = atoll(argv[1]);
  srv.request.repetitions = atoll(argv[2]);
  if (client.call(srv))
  {
      if(srv.response.success){
        ROS_INFO("Successful move");
      }
      else
      {
        ROS_INFO("Failed to move right");
      }
  }
  else
  {
    ROS_ERROR("Failed to call service move");
    return 1;
  }
  return 0;
}