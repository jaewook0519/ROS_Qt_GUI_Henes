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

    steeringAngleSub = nh.subscribe("/steering-angle", 1, &MainWindow::steeringAngleCallback, this);
    odomSub = nh.subscribe("/odom", 1, &MainWindow::odomCallback, this);
    depthSub = nh.subscribe("/depth", 1, &MainWindow::depthCallback, this);

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

void MainWindow::odomCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    odomValue = msg->linear_acceleration.x;
}

void MainWindow::depthCallback(const sensor_msgs::Image::ConstPtr& msg)
{
    //미완성
}

void MainWindow::updateUI()
{
    ui->steeringAngleLabel->setText(QString::number(steeringAngle));
    ui->odomLabel->setText(QString::number(odomValue));
    // ui->depthLabel->setPixmap(QPixmap::fromImage(depthImage));
}
