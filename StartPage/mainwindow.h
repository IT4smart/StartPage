#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qprocess.h>
#include <qsignalmapper.h>
#include <QVector>
#include <QPushButton>
#include <vector>
#include "./inc/init.h"

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

		Ui::MainWindow *ui; // user interface
		// delete the copy contructors, because they are not needed and
		// otherwise there will be problems with the copying of the ui* pointer
		MainWindow(const MainWindow&) = delete;
		MainWindow* operator=(const MainWindow&) = delete;
		QString exec_script(QString script_full_path);

        Init init; // init class

        // screen resolution
        void init_screen(int x, int y); // initialize screen with elements and correct resolution
        int get_screen_res_x();
        int get_screen_res_y();


        //void positionWidgets(); // hier werden die Elemente neu positioniert
    private slots:
        void on_btnExit_clicked();
	//	void on_btnCitrix_clicked();
	//	void on_btnDesktop_clicked(int);

	private:
        void fillWidgetsTexts(); // fill all widgets in correct texts and language
        bool fillNetworkLabels(); // fill all network labels in correct texts and language, return: true=connected, false=offline
    //    QProcess *procCitrix; // process for citrix
    //    QProcess *procSystem; // process for system commands
	//	QSignalMapper *signalMapper; // signal mapper zur übergabe der signale von signal nach slot
		//tests
	//	QStringList names;
	//	QStringList links;

        QPair<int,int> *screen_res; // screen resolution --> works only with 1 screen!


	protected:
        void timerEvent(QTimerEvent *event); // for clock

};

#endif // MAINWINDOW_H
