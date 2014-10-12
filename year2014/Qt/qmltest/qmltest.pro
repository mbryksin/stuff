#-------------------------------------------------
#
# Project created by QtCreator 2014-03-22T12:54:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qmltest
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

QT += declarative \
        script
#INCLUDEPATH += #Возможно может пригодится, просто укажите путь до директории include/qt-declarative/
