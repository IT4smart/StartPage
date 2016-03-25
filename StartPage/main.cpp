#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include <QDebug>
#include <startpage.h>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv); // create application

    // get screen resolution
    QDesktopWidget *dw = QApplication::desktop();
    int screen_res_w = dw->width(); //get screen resolution x --> works only with 1 screen!
    int screen_res_h = dw->height(); //get screen resolution y --> works only with 1 screen!

    // create window
    StartPage s; // constructor creates init-class
    s.init_screen(screen_res_w, screen_res_h); // initialize screen with actual screen resolution
    s.showFullScreen(); // show full screen

//    s.show();

    // end --> will never be reached, because of loop
    return a.exec();
}

