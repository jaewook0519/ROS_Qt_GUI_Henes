# ROS_Qt_GUI_Henes
**Install qt build for ROS Melodic**
```
sudo apt-get install ros-melodic-qt-build
```
**Create a catkin workspace**
```
mkdir -p ~/testui2_ws_ws/
cd ~/testui2_ws/
```
**Clone repository to src folder**
```
git clone https://github.com/jaewook0519/ROS_Qt_GUI_Henes.git
```
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
** **
```

```
