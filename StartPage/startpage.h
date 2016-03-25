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
        void init_screen(int w, int h); // initialize screen with elements and correct resolution

        // vars

    private:
        // functions
        bool getNetworkStatus(); // get network status --> return: true=connected, false=offline
        QString exec_script(QString script_full_path); // execution of script
        int get_screen_res_w();
        int get_screen_res_h();
        void startLoginCitrix(); // start citrix login
        void startLoginRdp(); // start rdp login

        // vars
        Ui::StartPage *ui; // user interface
        int screen_res_w; // screen resolution width --> works only with 1 screen!
        int screen_res_h; // screen resolution height --> works only with 1 screen!

    protected:
        void timerEvent(QTimerEvent *event); // for clock

    private slots:
        void on_tbtnNetStatus_clicked(); // network button
        void on_tbtnLogin_clicked(); // login button
        void slot_buffer(QByteArray); // slot to get return string of process
        void slot_buffer_error(QByteArray); // slot to get error string of process

};

#endif // STARTPAGE_H
