#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T16:38:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVTest
TEMPLATE = app

INCLUDEPATH += C:/OpenCV/include
LIBS    += C:/OpenCV/lib/libopencv_highgui2413.dll.a

SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui
