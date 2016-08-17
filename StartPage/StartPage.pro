#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T18:17:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = StartPage
TEMPLATE = app

HEADERS  += startpage.h \
            storebrowse.h \
    rdp.h

SOURCES += main.cpp \
        startpage.cpp \
        storebrowse.cpp \
    rdp.cpp

FORMS    += startpage.ui

RESOURCES += ressources.qrc
