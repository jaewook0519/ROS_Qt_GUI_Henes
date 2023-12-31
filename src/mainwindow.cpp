#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cv_bridge/cv_bridge.h>
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
    WaySteerControlSub = nh.subscribe("/Car_Control_cmd/SteerAngle_Int16",10, &MainWindow::WaySteerControlCallback, this);
    PIDcarspeedSub = nh.subscribe("PID_car_speed",10, &MainWindow::PIDcarspeedCallback, this);
    PIDerrorSub = nh.subscribe("PID_error",10, &MainWindow::PIDerrorCallback, this);
    encoderarduinoSub = nh.subscribe("encoder_arduino", 10, &MainWindow::encoderarduinoCallback, this);
    imudataSub = nh.subscribe("imu/data",1, &MainWindow::imudataCallback, this);

    gps_sub = nh.subscribe("/ublox_gps/fix", 10, &MainWindow::gpsCallback, this);
    pose_sub = nh.subscribe("/utm", 10, &MainWindow::poseCallback, this);

    cameraImageSub = nh.subscribe("/camera/color/image_raw", 1, &MainWindow::imageCallback, this);
    cameraImageSub2 = nh.subscribe("/camera/depth/image_rect_raw", 1, &MainWindow::imageCallback2, this);

    chatter_sub = nh.subscribe("chatter", 10, &MainWindow::chatterCallback, this);

    avoid_function_start_sub = nh.subscribe("avoid_function_start", 10, &MainWindow::avoidfunctionstartCallback, this);
    avoid_heading_angle_sub = nh.subscribe("avoid_heading_angle", 10, &MainWindow::avoidheadingangleCallback, this);

    linearVelocityValue = 0.0;
    angularVelocityValue = 0.0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUI()));
    timer->start(100); // UI 업데이트 주기
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PIDerrorCallback(const std_msgs::Float64::ConstPtr& msg)
{
    PIDerror = msg->data;
}

void MainWindow::PIDcarspeedCallback(const std_msgs::Int16::ConstPtr& msg)
{
    PIDcarspeed = msg->data;
}

void MainWindow::WaySteerControlCallback(const std_msgs::Int16::ConstPtr& msg)
{
    WaySteerControl = msg->data;
}

void MainWindow::steeringAngleCallback(const std_msgs::Float32::ConstPtr& msg)
{
    steeringAngle = msg->data;
}

void MainWindow::encoderarduinoCallback(const std_msgs::Float32::ConstPtr& msg)
{
    encoderarduino = msg->data;
}
void MainWindow::imudataCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    imudata = msg->orientation.w;
    imudatax = msg->orientation.x;
    imudatay = msg->orientation.y;
    imudataz = msg->orientation.z;
}

void MainWindow::odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    double linear_velocity = msg->twist.twist.linear.x;
    double angular_velocity = msg->twist.twist.angular.z;

    linearVelocityValue = linear_velocity;
    angularVelocityValue = angular_velocity;
}

/*
void MainWindow::poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    utmLatitude = msg->pose.position.x;
    utmLongitudefront = static_cast<int>(msg->pose.position.y);
    utmLongitudeback = msg->pose.position.y - utmLongitudefront;
}
*/

void MainWindow::poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    utmLatitude = msg->pose.position.x;
    double utmLongitude = msg->pose.position.y;

    std::stringstream ss;
    ss << std::fixed << std::setprecision(4) << utmLongitude;
    std::string utmLongitude2 = ss.str();
}

void MainWindow::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
    gpsLatitude = msg->latitude;
    gpsLongitude = msg->longitude;
}

void MainWindow::imageCallback(const sensor_msgs::Image::ConstPtr& msg)
{
    try
    {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
        QImage qimage(cv_ptr->image.data, static_cast<int>(cv_ptr->image.cols), static_cast<int>(cv_ptr->image.rows), static_cast<int>(cv_ptr->image.step), QImage::Format_RGB888);
        ui->cameraImageView->setPixmap(QPixmap::fromImage(qimage));
        ui->cameraImageView->setScaledContents(true);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}


void MainWindow::imageCallback2(const sensor_msgs::Image::ConstPtr& msg)
{
    try
    {
        cv_bridge::CvImagePtr cv_ptr2 = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
        QImage qimage(cv_ptr2->image.data, static_cast<int>(cv_ptr2->image.cols), static_cast<int>(cv_ptr2->image.rows), static_cast<int>(cv_ptr2->image.step), QImage::Format_RGB888);
        ui->cameraImageView2->setPixmap(QPixmap::fromImage(qimage));
        ui->cameraImageView2->setScaledContents(true);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}


void MainWindow::chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    QString message = QString::fromStdString(msg->data);
    ui->chattertextBrowser->append("Received String: " + message);
    target_string = msg->data;
}

void MainWindow::avoidfunctionstartCallback(const std_msgs::Bool::ConstPtr& msg)
{
    QString message = msg->data ? "true" : "false";
    ui->avoidfunctionstarttextBrowser->append("Avoid Function Start: " + message);
}

void MainWindow::avoidheadingangleCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
    QString message = "Right Angle: " + QString::number(msg->data[0]) +
                      " | Left Angle: " + QString::number(msg->data[1]);
    ui->avoidheadingangletextBrowser->append("Avoid Heading Angle: " + message);
}

void MainWindow::updateUI()
{
    ros::spinOnce();
    ui->steeringAngleLabel->setText(QString::number(steeringAngle));
    ui->WaySteerControlLabel->setText(QString::number(WaySteerControl));
    ui->PIDcarspeedLabel->setText(QString::number(PIDcarspeed));
    ui->PIDerrorLabel->setText(QString::number(PIDerror));
    ui->encoderarduinoLabel->setText(QString::number(encoderarduino));
    ui->linearVelocityLabel->setText(QString::number(linearVelocityValue));
    ui->angularVelocityLabel->setText(QString::number(angularVelocityValue));
    ui->imudataLabel->setText(QString::number(imudata));

    ui->imudataxLabel->setText(QString::number(imudatax));
    ui->imudatayLabel->setText(QString::number(imudatay));
    ui->imudatazLabel->setText(QString::number(imudataz));

    ui->utmLatitudeLabel->setText(QString::number(utmLatitude));

    ui->longitudeLabel->setText(QString::fromStdString(std::to_string(utmLongitude2)));


//    ui->utmLongitudefrontLabel->setText(QString::number(utmLongitudefront));
//    ui->utmLongitudebackLabel->setText(QString::number(utmLongitudeback));
}
