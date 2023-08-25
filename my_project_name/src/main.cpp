#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ros::init(argc, argv, "node_name"); // ROS 초기화

    MainWindow w(argc, argv);
    w.show();

    return a.exec();
}
