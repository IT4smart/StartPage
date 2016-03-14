#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qprocess.h>
#include <qsignalmapper.h>
#include <QVector>
#include <QPushButton>
#include <vector>

const QString SHELL_IP = "/home/test/Programs/qt-alex/HelloWorldGui/printIp.sh";
const QString SHELL_NETMASK = "/home/test/Programs/qt-alex/HelloWorldGui/printNetmask.sh";
const QString SHELL_GATEWAY = "/home/test/Programs/qt-alex/HelloWorldGui/printGateway.sh";
const QString BTN_CITRIX = "anmelden";
const QString BTN_CITRIX_TOOLTIP = "klicken zum Anmelden";
const QString STATUS_LINE_EMPTY = "";
const QString STATUS_LINE_WAIT = "... bitte warten ...";
const QString STATUS_LINE_SELECT_DESKTOP = "... bitte Desktop auswählen ...";
const QString GRP_BOX_NETWORK = "Netzwerk";
const QString LABEL_NETWORK_ONLINE = "verbunden";
const QString LABEL_NETWORK_OFFLINE = "offline";
const QString LABEL_IP = "IP-Adresse:";
const QString LABEL_NETMASK = "Netzmaske:";
const QString LABEL_GATEWAY = "Gateway:";
const QString LABEL_TYPE = "IP Vergabe:";

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void positionWidgets(); // hier werden die Elemente neu positioniert
        Ui::MainWindow *ui; // user interface

    private slots:
        void on_btnExit_clicked();
        void on_btnCitrix_clicked();
        void on_btnDesktop_clicked(int);

    private:
        QProcess *procCitrix; // process for citrix
        QProcess *procSystem; // process for system commands
        void fillWidgetsTexts(); // fill all widgets in correct texts and language
        bool fillNetworkLabels(); // fill all network labels in correct texts and language, return: true=connected, false=offline
        QSignalMapper *signalMapper; // signal mapper zur übergabe der signale von signal nach slot
//tests
        QStringList names;
        QStringList links;


    protected:
        void timerEvent(QTimerEvent *event); // for clock


};

#endif // MAINWINDOW_H
