#include "startpage.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv); // create application

    // get screen resolution
    QDesktopWidget *dw = QApplication::desktop();
    int screen_res_w = dw->width(); //get screen resolution x --> works only with 1 screen!
    int screen_res_h = dw->height(); //get screen resolution y --> works only with 1 screen!

    // create window
    StartPage s; // constructor creates init-class
    s.init_screen(screen_res_w, screen_res_h); // initialize screen with actual screen resolution
//    s.setWindowFlags(Qt::WindowStaysOnBottomHint); // window is always in background
    s.showFullScreen(); // show full screen
//    s.show();

    // enter application loop
    return a.exec();

}
