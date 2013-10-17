#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T18:05:30
#
#-------------------------------------------------

QT       += network
QT       += core gui opengl

TARGET = control-panel
TEMPLATE = app


SOURCES += main.cpp\
        panel.cpp \
    class/accelerometer.cpp \
    class/tcpconnector.cpp \
    class/gyroscope.cpp \
    class/motor.cpp \
    class/udpconnector.cpp \
    gui/customplot.cpp

HEADERS  += panel.h \
    class/accelerometer.h \
    class/tcpconnector.h \
    class/gyroscope.h \
    class/motor.h \
    class/udpconnector.h \
    gui/customplot.h \
    lib/qcustomplot.h
