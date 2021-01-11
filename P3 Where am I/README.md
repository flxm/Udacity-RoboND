# Project 3 - Where Am I?

Create a ROS package that launches a custom robot model in a custom Gazebo world

Utilize the ROS AMCL package and the Tele-Operation / Navigation Stack to localize the robot

Explore, add, and tune specific parameters corresponding to each package to achieve the best possible localization results

## How to use

* Make catkin

```sh
catkin_make
source devel/setup.bash
```

* Run Gazebo and RViz

```sh
roslaunch my_robot world.launch
```

* Run Teleop

```sh
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```

* Run AMCL in separate terminal

```sh
roslaunch my_robot amcl.launch
```
