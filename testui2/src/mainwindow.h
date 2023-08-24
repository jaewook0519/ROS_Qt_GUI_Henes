#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void steeringAngleCallback(const std_msgs::Float32::ConstPtr& msg);
    void odomCallback(const sensor_msgs::Imu::ConstPtr& msg);
    void depthCallback(const sensor_msgs::Image::ConstPtr& msg);
    void updateUI();

private:
    Ui::MainWindow *ui;
    ros::NodeHandle nh;
    ros::Subscriber steeringAngleSub;
    ros::Subscriber odomSub;
    ros::Subscriber depthSub;
    float steeringAngle;
    float odomValue;
    QImage depthImage;

    QTimer *timer;
};

#endif // MAINWINDOW_H
