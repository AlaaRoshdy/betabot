# Betabot Moving in Square

- [Betabot Moving in Square](#betabot-moving-in-square)
  - [Project Description](#project-description)
  - [GUIDE](#guide)
  - [After you implement the pkg state your reflection below](#after-you-implement-the-pkg-state-your-reflection-below)
    - [How did you plan the task?](#how-did-you-plan-the-task)
    - [What ROS REPs did you used?](#what-ros-reps-did-you-used)
    - [How we could increase the overall performance?](#how-we-could-increase-the-overall-performance)
    - [List the most time consuming problems you faced](#list-the-most-time-consuming-problems-you-faced)

  - [Demo](#demo)
  - [Screenshot](#screenshot)
      - [NAME:](#name)
      - [ID:](#id)

## Project Description 

Create a ROS package with custom service/action c++/python to move the betabot in gazebo, the movement
triggered will have to be a square, like in the image below:
Betabot movement Use the data passed to this topic /move_betabot_in_square_custom to change the way
betabot moves. Depending on the side value, the service must move the robot in a square
movement based on the side given. Also, the robot must repeat the shape as many times as
indicated in the repetitions variable of the message. Finally, it must return True if everything
went OK in the success variable.


## GUIDE

1. Create a new launch file, called start_betabot_move_custom_service_server.launch,
that launches the new betabot_move_custom_service_server.py file.
2. Test that when calling this new /move_betabot_in_square_custom service, betabot
moves accordingly. This means, the square is performed taking into account the side
and repetitions variables.
3. Create a new service client that calls the service /move_betabot_in_square_custom,
and makes betabot moves in a small square twice and in a bigger square once.
It will be called betabot_move_custom_service_client.py. The launch that starts it will
be called call_betabot_move_in_square_custom_service_server.launch.
4. Refer to this tutorial for more help.
The BetabotCustomServiceMessage.srv will be something like this:

```sh
float64 side # The distance of each side of the square
int32 repetitions # The number of times the betabot robot has to execute the square
movement when the service is called
---
bool success # Did it achieve it?
```

>NOTE: The side variable doesn’t represent the real distance along each size of the square.It’s just a variable that will be used to change the size of the square. The bigger the size variable is, the bigger the square performed by the robot will be. You can use any robot pkg.

>To make you project standout try another shape and to use filtered `odemtry` data.

---

## After you implement the pkg state your reflection below

### How did you plan the task?
 I used server/client to send a request and execute that request. The client's parameters are the size of the square and the number of times the robot moves in a square.
    Implementing moving forward was a simple task of reading the odom data and determining the difference between the initial position of the robot and the final position. For the 90 degree rotation, it wasnt as straightforward. This is due to the fact that the angle readings range from -PI to PI, so subtracting the initial angle from the final angle would not always lead to the correct angle difference. To solve this problem 

### What ROS REPs did you used?
The REPs used in C++ like organizing all data in folders launch, src, srv (if there is server/client or server/action). Also the naming conventions.

### How we could increase the overall performance?
 Using a PID controller to tune the robot's position and angle and recieve constant feedback from the environment. 

### List the most time consuming problems you faced
 Changing my code from py to cpp, and finding the right way to get the angle difference.

---

## Demo
Add unlisted youtube/drive video

[Demo](https://drive.google.com/file/d/1Yvx6djcdScz8EPaaXY69ytUgMSndccsI/view?usp=sharing)

## Screenshot

[image](yourscreenshot)

---

#### NAME:
Alaa Mohamed Roshdy
#### ID:
201600031
---
