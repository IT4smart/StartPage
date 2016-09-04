#define SYSLOG(INFO)

#include "startpage.h"
#include "easylogging++.h"
#include <QApplication>
#include <QDesktopWidget>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {

    // Load configuration from file
    el::Configurations conf("../Ressources/logger.conf");
    // Reconfigure single logger
    el::Loggers::reconfigureLogger("default", conf);
    // Actually reconfigure all loggers instead
    el::Loggers::reconfigureAllLoggers(conf);
    // Now all the loggers will use configuration from file

    ELPP_INITIALIZE_SYSLOG("IT4S-StartPage", LOG_PID | LOG_CONS | LOG_PERROR, LOG_USER);

    START_EASYLOGGINGPP(argc, argv);

    //Logging info
    SYSLOG(INFO) << "StartPage is starting.";

    QApplication a(argc, argv); // create application

    // get screen resolution
    QDesktopWidget *dw = QApplication::desktop();
    int screen_res_w = dw->width(); //get screen resolution x --> works only with 1 screen!
    int screen_res_h = dw->height(); //get screen resolution y --> works only with 1 screen!

    SYSLOG(DEBUG) << "Screen width: " << screen_res_w << "; Screen height: " << screen_res_h;

    // create window
    StartPage s; // constructor creates init-class
    s.init_screen(screen_res_w, screen_res_h); // initialize screen with actual screen resolution
//    s.setWindowFlags(Qt::WindowStaysOnBottomHint); // window is always in background

    SYSLOG(DEBUG) << "Screen is set to fullscreen";

    s.showFullScreen(); // show full screen
//    s.show();

    // enter application loop
    return a.exec();

}
