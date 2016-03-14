#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T13:19:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloWorldGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Citrix.cpp

HEADERS  += mainwindow.h \
    Citrix.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

CONFIG += c++11
