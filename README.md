# ROS_Qt_GUI_Henes
**Install qt build for ROS Melodic**
```
sudo apt-get install ros-melodic-qt-build
```
**Create a catkin workspace**
```
mkdir -p ~/testui2_ws
cd ~/testui2_ws
```
**Clone repository to src folder**
```
git clone https://github.com/jaewook0519/ROS_Qt_GUI_Henes.git
```
"Open the ROS_Qt_GUI_Henes file and move all internal files to testui2_ws"


**Catkin make**
```
cd ~/testui2_ws/
catkin_make
source devel/setup.bash
```
**rosmaster**
```
roscore
```
**run gui**
```
rosrun testui2 testui2
```
**set arduino**
```
sudo chmod 666 /dev/ttyUSB0
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0
```
**test turtlebot code**
```
export LSD_MODEL=LSD-01
roslaunch turtlebot3_bringup turtlebot3_robot.launch
```
![image](https://github.com/jaewook0519/ROS_Qt_GUI_Henes/assets/141805195/b4fc1709-50c7-4b53-840f-0c8dd1eb23e7)

