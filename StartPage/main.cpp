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
    s.init_screen(screen_res_w,screen_res_h); // initialize screen with actual screen resolution
    s.showFullScreen();
//    s.show();




 /*   MainWindow w; // constructor creates init-class
    w.setWindowFlags(Qt::WindowStaysOnTopHint); // window stays on top
    w.showFullScreen(); // show window as full screen
    w.init_screen(x,y); // save the screen resolution in init class

    // move all widgets according to screen size (basis is set to 1024x768)
/*    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    w.ui->widgetContainer->move((width-1024)/2,(height-768)/2);
*/
    // end
    return a.exec();
}

