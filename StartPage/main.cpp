#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include "Citrix.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    // show window as full screen
    w.showFullScreen();
//    w.show();

    // move all widgets according to screen size (basis is set to 1024x768)
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    w.ui->widgetContainer->move((width-1024)/2,(height-768)/2);

    // end
    return a.exec();
}

