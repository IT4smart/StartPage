#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include "./inc/init.h"
#include "./inc/citrix.h"
#include <qprocess.h>
#include <qsignalmapper.h>
#include <QVector>
#include <QPushButton>
#include <vector>
#include <QVBoxLayout>

/*************
 * Possible log level:
 * DEBUG --> The message is only for debugging purposes.
 * INFO --> The message is purely informational.
 * NOTICE --> The message describes a normal but important event.
 * WARNING --> The message is a warning.
 * ERR --> The message describes an error.
 * CRIT --> The message states a critical condition.
 * ALERT --> Action on the message must be taken immediately.
 * EMERG --> The message says the system is unusable.
 *************/
const QString IT4S_LOG_LEVEL = "DEBUG";

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
        void startConfigPage(); // start the configurationpage

        // vars
        Ui::StartPage *ui; // user interface
        int screen_res_w; // screen resolution width --> works only with 1 screen!
        int screen_res_h; // screen resolution height --> works only with 1 screen!
        QSignalMapper *signalMapper; // signal mapper maps the desktop button signals to the desktop slot
        QList<QPair<QString,QString>> desktops_list; // list of desktops
        Citrix *ctx; // save citrix class for later
        QVBoxLayout *ctx_desktop_v_layout; // save QVBoxLayout for buttons --> later delete this, and all buttons are gone



    protected:
        void timerEvent(QTimerEvent *event); // for clock

    private slots:
        void on_tbtnNetStatus_clicked(); // network button
        void on_tbtnLogin_clicked(); // login button
        void on_btnDesktop_clicked(int index); // slot der geklickte desktops abfängt

};

#endif // STARTPAGE_H
