#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T13:19:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Startpage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ./src/citrix.cpp \
    ./src/init.cpp \
    ../../libs/tools/src/custom_exceptions.cpp \
    ../../libs/tools/src/exec_cmd.cpp \
    ../../libs/tools/src/IniFile.cpp \
    ../../libs/tools/src/ini_parser.cpp \
    ../../libs/tools/src/maps.cpp \
    ../../libs/tools/src/remove_file.cpp \
    ../../libs/tools/src/set_permission.cpp \
    ../../libs/tools/src/setting.cpp \
    startpage.cpp


HEADERS  += mainwindow.h \
    ./inc/citrix.h \
    ./inc/init.h \
    ../../libs/tools/inc/custom_exceptions.h \
    ../../libs/tools/inc/exec_cmd.h \
    ../../libs/tools/inc/IniFile.h \
    ../../libs/tools/inc/ini_parser.h \
    ../../libs/tools/inc/maps.h \
    ../../libs/tools/inc/remove_file.h \
    ../../libs/tools/inc/set_permission.h \
    ../../libs/tools/inc/setting.h \
    startpage.h



FORMS    += mainwindow.ui \
    startpage.ui

RESOURCES += \
    resources.qrc

CONFIG += c++11
