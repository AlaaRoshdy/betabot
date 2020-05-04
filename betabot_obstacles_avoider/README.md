# Betabot Obstacle avoider

- [Betabot Obstacle avoider](#betabot-obstacle-avoider)
  - [Project Description](#project-description)
  - [After you implement the pkg state your reflection below](#after-you-implement-the-pkg-state-your-reflection-below)
    - [How did you plan the task?](#how-did-you-plan-the-task)
    - [what is your logic?](#what-is-your-logic)
    - [What ROS REPs did you used?](#what-ros-reps-did-you-used)
    - [How we could increase the overall performance?](#how-we-could-increase-the-overall-performance)
    - [List the most time consuming problems you faced](#list-the-most-time-consuming-problems-you-faced)
    - [Demo](#demo)
    - [Screenshot](#screenshot)
      - [NAME:](#name)
      - [ID:](#id)

## Project Description 

Create a ROS package with custom nodes c++/python to move the
betabot randomly in gazebo, the movement should be triggered then the robot
moves randomly while avoid objects based on laser scans reading based on the laser
scans.


>NOTE: DON'T process one ray of the laser scans array or it will be considered ultrasonic/IR sensor.try to come up with approach thats use the laser full potential. 

>To make you project standout try not to visit any place twice.

---

## After you implement the pkg state your reflection below
### How did you plan the task?
First, I had to understand the laserScan data and what it represents and how to use it. Then, started formulating a logic for dealing with data and created a py node to move the robot accordingly.
### what is your logic?
 First, I divide the laserScan data into data from the front, left and right. Then, I get the minimum distance from all 3 directions. If the closest object coming in front of the robot is more than 1.0 units away, the robot moves forward. If not, then the object will check if there is an obstacle on its right by checking the closest object on its right. If it's further from 1.0 units, then the robot will move right. Else, the robot will move left.
### What ROS REPs did you used?
 The REPs used in python like organizing all data in folders launch, src, srv (if there is server/client or server/action). Also the naming conventions.
### How we could increase the overall performance?
 Segment the laserScan into 5 segements, each giving an insight on where and how close objects are. This would make object avoidance more accurate. Also, instead of rotating randomly left or right, rotating based on which direction has the furthest obstacle.
### List the most time consuming problems you faced
Deciding how to segment the laserscan efficiently so that it avoids objects in any direction accordingly.

---

### Demo
Add unlisted youtube/drive video

[Demo](yourlinkhere)

### Screenshot

[image](yourscreenshot)

---

#### NAME:
Alaa Mohamed Roshdy
#### ID:
201600031

---
