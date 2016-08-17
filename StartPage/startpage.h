#ifndef STARTPAGE_H
#define STARTPAGE_H

#include "storebrowse.h"
#include "rdp.h"
#include <QMainWindow>
#include <QTimerEvent>
#include <QSettings>
#include <QApplication>
#include <QVariant>
#include <QDebug>
#include <QPair>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QtNetwork/QNetworkConfigurationManager>


// constants
const QString SETTINGS_PATH = "../Ressources/settings.ini"; // hier werden settings gespeichert
// global keys
const QString LOGO_PATH = "global/logo_path"; // key für settings.ini
const QString CITRIX_RDP_TYPE = "global/citrix_rdp_type";
// network keys
const QString NETWORK_TYPE = "network/type"; // key for settings.ini
// citrix keys
const QString NETSCALER_URL = "citrix/netscaler_url";
const QString STORE_URL = "citrix/store_url";
const QString CITRIX_DOMAIN = "citrix/domain";
// rdp keys
const QString RDP_DOMAIN = "rdp/domain"; // key
const QString RDP_URL = "rdp/server_url"; // key
// scripts
const QString PRG_SHELL = "/bin/sh";
const QString PRG_CONFIG_PAGE = "../Ressources/scripts/startConfigPage.sh";
const QString PRINT_IP = "../Ressources/scripts/printIp.sh"; // gib IP zurück wenn connected, sonst leer
const QString PRINT_NETMASK = "../Ressources/scripts/printNetmask.sh"; // gib Netmask zurück wenn connected, sonst leer
const QString PRINT_GATEWAY = "../Ressources/scripts/printGateway.sh"; // gib Gateway zurück wenn connected, sonst leer
// predefined texts
const QString LE_USER_TEXT = "Username ohne Domäne";


namespace Ui {
    class StartPage;
}

class StartPage : public QMainWindow {
    Q_OBJECT

    public:
        // FUNCTIONS
        explicit StartPage(QWidget *parent = 0); // constructor
        ~StartPage(); // desctructor
        void init_screen(int w, int h); // initialize screen with elements and correct resolution
        static QPair<QString,QString> exec_cmd_process(QString command); // execute commands

        // VARS
        QNetworkConfigurationManager *nwManager; // NetworkManager from Qt to get status of networkinterfaces.

    private:
        // FUNCTIONS
        void doTests(); // delete later, for testing only
        void startConfigPage(); // ConfigPage will be started and StartPage will be killed
        QVariant getSettingsValue(QString settingsKey); // get Settings value of Settings Key
        bool getNetworkStatus(); // get network status --> return: true=connected, false=offline
        void loginCitrix(); // start citrix login
        void loginRdp(); // start rdp login
        void setLogin(bool enable); // true=enable, false=disable
        void changeNetworkLogo(); // change network logo

        // VARS
        Ui::StartPage *ui; // manage the UI
        int screen_res_w; // screen resolution width --> works only with 1 screen!
        int screen_res_h; // screen resolution height --> works only with 1 screen!
        QString citrix_rdp_type; // store in which mode is the StartPage
        bool isFirstChange; // true: line edit User had no entry yet --> initial text still there
                        // false: not the first
        int mouseClickCount; // 0, 1 or 2 (= double click) DOES NOT WORK !!!
        // for citrix
        Storebrowse *storebrowse; // actual storebrowse instance
        QSignalMapper *signalMapper; // signal mapper maps the desktop button signals to the desktop slot
        QList<QPair <QString,QString>> desktops_list; // list of desktops
        QVBoxLayout *ctx_desktop_v_layout; // save QVBoxLayout for buttons --> later delete this, and all buttons are gone
        // for rdp
        Rdp *rdp; // actual rdp instance


    protected:
        void timerEvent(QTimerEvent *tevent); // for clock

    private slots:
        void on_btnLogin_clicked(); // login button (citrix or rdp)
        void on_tbtnNetStatus_clicked(); // show net status
        void on_btnDesktop_clicked(int index); // slot der geklickte desktops abfängt (for CITRIX only)
        void on_leUser_TextChanged(); // text was changed in line edit field

};

#endif // STARTPAGE_H
