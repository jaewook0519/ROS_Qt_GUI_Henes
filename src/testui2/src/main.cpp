#include "mainwindow.h"
#include <QApplication>
#include <ros/ros.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "testui2");
    ros::NodeHandle nh;

    QApplication a(argc, argv);
    MainWindow w;

    ros::Subscriber steeringAngleSub = nh.subscribe("/steering_angle", 1, &MainWindow::steeringAngleCallback, &w);
    ros::Subscriber odomSub = nh.subscribe("/odom", 1, &MainWindow::odomCallback, &w);

    w.show();

    QTimer rosTimer; // QTimer 객체 생성
    rosTimer.setInterval(10); // 타이머 간격 설정 (10ms)

    // QTimer의 timeout 시그널이 발생할 때마다 ros::spinOnce() 호출
    QObject::connect(&rosTimer, &QTimer::timeout, [](){
        ros::spinOnce();
    });
    rosTimer.start(); // 타이머 시작

    return a.exec();
}
