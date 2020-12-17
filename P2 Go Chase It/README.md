# Project 2 - Go Chase It!

This is a simple differential-drive robot housed in single floor building simulated in Gazebo. The robot is controlled by ROS. The robot is equipped with camera and Hokuyo laser scanner.

## How to use

* Make catkin

```sh
catkin_make
source devel/setup.bash
```

* Run ROS
```sh
roslaunch my_robot world.launch
```

* Run process_image and drive_bot nodes
```sh
roslaunch ball_chaser ball_chaser.launch
```

## Nodes

Two nodes are essential for **white** ball chasing:

* `process_image` - subsribes images from camera and detect a *white* object in it. This node also calls drive_bot service to steer robot towards the object.
* `drive_bot` - service to drive robot (moving froward, backwards, turn around its vertical axis)

## Robot

The robot is described in my_robot.urdf file. It is a two-wheeled round-shaped vehicle. It is equipped with a camera and Hokuyo laser scanner.
