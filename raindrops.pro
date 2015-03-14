#-------------------------------------------------
#
# Project created by QtCreator 2015-02-06T13:11:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raindrops
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp \
    instructions.cpp

HEADERS  += mainwindow.h \
    gameboard.h \
    instructions.h

FORMS    += mainwindow.ui \
    gameboard.ui \
    instructions.ui

RESOURCES +=

CONFIG  +=c++11
