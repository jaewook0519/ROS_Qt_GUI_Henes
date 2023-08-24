cmake_minimum_required(VERSION 3.0.2)
project(testui2)

set(CMAKE_AUTOUIC ON)
find_package(
    catkin REQUIRED
    COMPONENTS
    qt_build
    roscpp
    std_msgs
    sensor_msgs
    image_transport
    cv_bridge
    )

include_directories(${catkin_INCLUDE_DIRS})
catkin_package()

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets)
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
include_directories(
    ${catkin_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    )

set(QT_SOURCES
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    )

add_executable(testui2 src/main.cpp src/mainwindow.cpp)
target_link_libraries(testui2 ${QT_LIBRARIES} ${catkin_LIBRARIES}
        Qt5::Core     Qt5::Widgets)
install(TARGETS testui2 RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
target_link_libraries(testui2 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
## Install nodes code
## install(TARGETS node_name RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
