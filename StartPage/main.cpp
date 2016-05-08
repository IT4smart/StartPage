#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include <QDebug>
#include <string.h>
#include "startpage.h"


int main(int argc, char *argv[]) {
    
    if (argc == 1) {
        QApplication a(argc, argv); // create application

        // get screen resolution
        QDesktopWidget *dw = QApplication::desktop();
        int screen_res_w = dw->width(); //get screen resolution x --> works only with 1 screen!
        int screen_res_h = dw->height(); //get screen resolution y --> works only with 1 screen!

        // create window
        StartPage s; // constructor creates init-class
        s.init_screen(screen_res_w, screen_res_h); // initialize screen with actual screen resolution
        s.setWindowFlags(Qt::WindowStaysOnBottomHint); // window is always in background
        s.showFullScreen(); // show full screen
        //s.show();

        // end --> will never be reached, because of loop
        return a.exec();
    } else {
        if (strcmp(argv[1], "-v") == 0) {
            // print version
            std::cout << "Version: " << StartPage_VERSION_MAJOR << "." << StartPage_VERSION_MINOR << "." << StartPage_VERSION_PATCH << "\n";
        }
    }
}

