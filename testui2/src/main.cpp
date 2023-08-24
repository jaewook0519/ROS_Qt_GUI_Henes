#include "mainwindow.h"
#include <QApplication>
#include <ros/ros.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "testui2");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ros::NodeHandle nh;
    //ROS 관련 작업, 노드 실행 ros::spin()
    //ROS 토픽 구독 코드 추가

    return a.exec();
}
