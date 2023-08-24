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
    ros::Subscriber steeringAngleSub = nh.subscribe("/steering_angle", 1, &MainWindow::steeringAngleCallback, &w);
    ros::Subscriber odomSub = nh.subscribe("/odom", 1, &MainWindow::odomCallback, &w); 
    ros::spin();

    return a.exec();
}
