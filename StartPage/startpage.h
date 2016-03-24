#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include "./inc/init.h"

#include <qprocess.h>
#include <qsignalmapper.h>
#include <QVector>
#include <QPushButton>
#include <vector>


namespace Ui {
    class StartPage;
}

class StartPage : public QMainWindow
{
    Q_OBJECT

    public:
        // conststructor, destructor
        explicit StartPage(QWidget *parent = 0); // constructor
        ~StartPage(); // desctructor
        StartPage(const StartPage&) = delete; // delete the copy contructors, because they are not needed and
        StartPage* operator=(const StartPage&) = delete; // otherwise there will be problems with the copying of the ui* pointer

        // functions
        Init init; // init class
        QString exec_script(QString script_full_path); // execution of script
        void init_screen(int w, int h); // initialize screen with elements and correct resolution
        int get_screen_res_w();
        int get_screen_res_h();

        // vars

    private:
        // functions
        bool getNetworkStatus(); // get network status --> return: true=connected, false=offline

        // vars
        Ui::StartPage *ui; // user interface
        int screen_res_w; // screen resolution width --> works only with 1 screen!
        int screen_res_h; // screen resolution height --> works only with 1 screen!

    protected:
        void timerEvent(QTimerEvent *event); // for clock

    private slots:
        void on_tbtnNetStatus_clicked(); // network button
};

#endif // STARTPAGE_H
