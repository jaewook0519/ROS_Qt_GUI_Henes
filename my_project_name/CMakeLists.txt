cmake_minimum_required(VERSION 2.8.3)
project(my_project_name)

find_package(catkin REQUIRED COMPONENTS
  qt_build
  roscpp
  rospy
  std_msgs
  nav_msgs
)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs nav_msgs qt_build rospy
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(my_project_name
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
)

target_link_libraries(my_project_name
  ${catkin_LIBRARIES}
  Qt5::Widgets
)

install(TARGETS my_project_name
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
