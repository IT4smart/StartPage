#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv); // application

    // create desktop
    QDesktopWidget dw;
    int x=dw.width(); //get screen resolution x
    int y=dw.height(); //get screen resolution y
    qDebug() << "x,y=" << x << "*" << y <<"\n";

    // create window
    MainWindow w;
    w.setWindowFlags(Qt::WindowStaysOnTopHint); // window stays on top
    w.showFullScreen(); // show window as full screen
//    w.show();

    // move all widgets according to screen size (basis is set to 1024x768)
/*    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    w.ui->widgetContainer->move((width-1024)/2,(height-768)/2);
*/
    // end
    return a.exec();
                }

