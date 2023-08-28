#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <QThread>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    steeringAngleSub = nh.subscribe("/steering_angle", 1, &MainWindow::steeringAngleCallback, this);
    odomSub = nh.subscribe("/odom", 1, &MainWindow::odomCallback, this);

    // Initialize the velocity values
    linearVelocityValue = 0.0;
    angularVelocityValue = 0.0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUI()));
    timer->start(100); // UI 업데이트 주기 (100ms)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::steeringAngleCallback(const std_msgs::Float32::ConstPtr& msg)
{
    steeringAngle = msg->data;
}

void MainWindow::odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    double linear_velocity = msg->twist.twist.linear.x;
    double angular_velocity = msg->twist.twist.angular.z;

    // Update velocity values
    linearVelocityValue = linear_velocity;
    angularVelocityValue = angular_velocity;
}

void MainWindow::updateUI()
{
    ui->steeringAngleLabel->setText(QString::number(steeringAngle));
    ui->linearVelocityLabel->setText(QString::number(linearVelocityValue));
    ui->angularVelocityLabel->setText(QString::number(angularVelocityValue));
}
