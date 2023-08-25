#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int argc, char *argv[], QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    steeringAngleSub = nh.subscribe("/steering_angle", 1, &MainWindow::steeringAngleCallback, this);
    odomSub = nh.subscribe("/odom", 1, &MainWindow::odomCallback, this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::steeringAngleCallback(const std_msgs::Float32::ConstPtr& msg)
{
    // /steering_angle 토픽에서 데이터를 받아와서 출력
    ui->lcdNumber->display(msg->data);
}

void MainWindow::odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    // /odom 토픽에서 데이터를 받아와서 출력
    ui->lcdNumber_2->display(msg->twist.twist.linear.x);
}
