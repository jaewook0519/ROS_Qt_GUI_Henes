#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char *argv[], QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void steeringAngleCallback(const std_msgs::Float32::ConstPtr& msg);
    void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);

private:
    Ui::MainWindow *ui;
    ros::NodeHandle nh;
    ros::Subscriber steeringAngleSub;
    ros::Subscriber odomSub;
};

#endif // MAINWINDOW_H
