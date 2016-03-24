#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./inc/citrix.h"
#include "../../libs/tools/inc/custom_exceptions.h"
#include "../../libs/tools/inc/exec_cmd.h"
#include <iostream>
#include <qprocess.h>
#include <QTime>
#include <QTextStream>
#include <QObject>
#include <QStringList>
#include <QSignalMapper>
#include <QApplication>
#include <QDebug>

//
// Konstruktor
//
/** 
 * Constructor
 * very important: initialiaze init with a string. Otherwise the contructor without argument would be chosen, 
 * and in there, an developer_error exception can be thrown. 
 *
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), init("empty")
					  //, procCitrix(nullptr), procSystem(nullptr), signalMapper(nullptr), names(), links()
{
	ui->setupUi(this);

    // initialize vars with init-constructor
	try {
		init = Init();
	} catch(const developer_error& e) {
		//TODO
		//handle the error
		std::cout << -1 << "Load Setting in Init-Konstruktor failed" << std::endl;
	}

    // start clock
    QTime qtime = QTime::currentTime(); //Timer auslesen
    QString stime = qtime.toString(Qt::LocalDate);//Timerwert als String wandeln
    ui->lblClock->setText(stime);//Text von Label setzen
    startTimer(1000);


//std::cout << exec_script(SHELL_IP).toStdString() << std::endl;
}

/**
 * destructor
 */
MainWindow::~MainWindow() {
	delete ui;
}

/** @brief init_screen
 * @param x
 * @param y
 */
void MainWindow::init_screen(int screen_w, int screen_h) {
    // save screen resolution
    screen_res = new QPair<int,int>(screen_w, screen_h);

    // position logo
    QString logo_path = init.get_client_logo();
    QPixmap imgLogo(logo_path);
    int logo_w = 0.1 * screen_w; // width of logo
    int logo_h = 0.1 * screen_h; // height of logo
    int logo_offset_w = 0.05 * screen_w; // pos of left top corner
    int logo_offset_h = 0.05 * screen_h; // pos of left top corner
    ui->lblLogo->setGeometry(logo_offset_w, logo_offset_h, logo_w, logo_h);
    ui->lblLogo->setPixmap(imgLogo.scaled(logo_w, logo_h, Qt::KeepAspectRatio, Qt::FastTransformation));
//    QLabel* l = new QLabel;
//    l->setParent(ui->centralWidget);
//    l->setGeometry(logo_offset_w,logo_offset_h,logo_w+logo_offset_w,logo_h+logo_offset_h);
//    l->setPixmap(imgLogo.scaled(logo_w, logo_h, Qt::KeepAspectRatio, Qt::FastTransformation));

    // position clock
    int clock_w = 0.1 * screen_w; // width of clock
    int clock_h = 0.1 * screen_h; // height of clock
    int clock_offset_w = 0.05 * screen_w; // pos of left top corner
    int clock_offset_h = 0.85 * screen_h; // pos of left top corner
    ui->lblClock->setGeometry(100,720,200,100);
//    FRAMELAYOUT statt QMAINWINDOW ????
//    ui->lblClock->setGeometry(clock_offset_w, clock_offset_h, clock_w, clock_h);
//    ui->lblClock->setText("TEST");
//    ui->lblClock->show();

    // fill widgets with texts
    MainWindow::fillWidgetsTexts();

}

/**
 * @brief get_screen_res_x
 * @return
 */
int MainWindow::get_screen_res_x() {
    return screen_res->first;
}

/**
 * @brief get_screen_res_y
 * @return
 */
int MainWindow::get_screen_res_y() {
    return screen_res->second;
}





/* 
   void init(){
   app_mode = ;

   if (app_mode = citrix) {

   }
   }
   }

 *
 *
 * */


/* 
//
// button Desktop
//
void on_btnDesktop_clicked() {
qDebug("*** WORKED ***");
}

//
// position widgets
//
void MainWindow::positionWidgets() {
ui->lblClock->move(this->geometry().center()); // funktioniert !!!
ui->lblClock->updateGeometry();
}
*/
//
// button Exit
void MainWindow::on_btnExit_clicked() {
    QApplication::exit();
}
/*
//
// button Citrix
//
void MainWindow::on_btnCitrix_clicked() {
// change ui
ui->lblStatusLine->setText(STATUS_LINE_WAIT); // set status line
//    ui->lblStatusLine->repaint();
ui->btnCitrix->hide(); //->deleteLater(); // hide button oder delete button ...
ui->centralWidget->repaint();

// show stores

// select store

// show desktops

// select desktop

// start desktop


procCitrix = new QProcess(this); // start process for citrix

procCitrix->start("sh");
//    procCitrix->write("/opt/Citrix/ICAClient/util/storebrowse -l extern.ass-hn.de");
//    procCitrix->write("/opt/Citrix/ICAClient/util/storebrowse -a extern.ass-hn.de");
procCitrix->write("/opt/Citrix/ICAClient/util/storebrowse -E 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'");
//    procCitrix->write("/opt/Citrix/ICAClient/util/storebrowse -L 'ddcxd1.W7 Lehrer Test $S5-3' 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'");
procCitrix->closeWriteChannel();

QByteArray buffer;
QByteArray buffer_error;
while(procCitrix->waitForFinished()) {
buffer.append(procCitrix->readAllStandardOutput());
buffer_error.append(procCitrix->readAllStandardError());
}
procCitrix->close();

//qDebug(buffer.data());
ui->lblDebugLine->setText(QString(buffer_error).toLatin1());

// split str
QString sbuf = buffer.data();
sbuf.remove("'"); // remove '-zeichen
QStringList zeilen = sbuf.split("\n", QString::SkipEmptyParts);

// trenne in Zeilen
for (int i=0;i<zeilen.size();i++) {
// trenne in Spalten
QStringList spalten = zeilen.at(i).split("\t", QString::SkipEmptyParts);
names.push_back(spalten.at(1).toLocal8Bit());
links.push_back(spalten.at(0).toLocal8Bit());
}

ui->lblStatusLine->setText(STATUS_LINE_SELECT_DESKTOP); // set status line

// baue neue Buttons auf
signalMapper = new QSignalMapper(this); // signal mapper zur übergabe von daten von signals to slots
for (int i=0;i<names.size();i++) {
	QPushButton *btn = new QPushButton(names.at(i)); // create button
	btn->setFont(QFont("Calibri", 26)); // set font
	ui->hLayoutElements->addWidget(btn); // add button to layout
	signalMapper->setMapping(btn, i); // setze mapper
	connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map())); // connect btn to slot map
}
connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(on_btnDesktop_clicked(int)));

//    QObjectList chlist = ui->hLayoutElements->children();
//    qDebug("childn0="+chlist.size());
}

//
// button event von gedrücktem button
//
void MainWindow::on_btnDesktop_clicked(int index) {
	qDebug() << "*** on_btnDesktop_clicked: " << names.at(index);
	// change ui
	QObjectList childrenList = ui->horizontalLayoutWidget->children();
	for (int i=0;i<childrenList.size();i++) {
		qDebug() << "name= " << childrenList.at(i)->objectName() << ", class= " << childrenList.at(i)->metaObject()->className();
		QString cname = childrenList.at(i)->metaObject()->className();
		if (cname=="QPushButton") { // hide and delete all buttons
			//            qDebug() << "ok ...";
			QPushButton *temp = qobject_cast<QPushButton *>(childrenList.at(i));
			temp->hide(); // hide button
			temp->disconnect(); // disconnect from signals
			temp->deleteLater(); // finally delete object
		}
	}
	//    signalMapper->removeMappings();

	//    QPushButton *ui_findChild = ui->centralWidget->findChild<QPushButton *>(names.at(0));
	//qDebug() << ui_findChild->accessibleName();
	//ui->hLayoutElements->removeWidget(ui_findChild);

	ui->lblStatusLine->setText(STATUS_LINE_WAIT); // set status line
	ui->centralWidget->repaint(); // update page

	procCitrix = new QProcess(this); // start process for citrix
	procCitrix->start("sh");
	procCitrix->write("/opt/Citrix/ICAClient/util/storebrowse -L '"+links.at(index).toLatin1()+"' 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'");
	procCitrix->closeWriteChannel();

	QByteArray buffer;
	QByteArray buffer_error;
	while(procCitrix->waitForFinished()) {
		buffer.append(procCitrix->readAllStandardOutput());
		buffer_error.append(procCitrix->readAllStandardError());
	}
	procCitrix->close();

	qDebug(buffer.data());
	ui->lblDebugLine->setText(QString(buffer_error));
}
*/

//
// process timer event
//
void MainWindow::timerEvent(QTimerEvent *event) {
	//TODO
	(void) event;
	// gebe Zeit aus
	QTime qtime = QTime::currentTime();
	QString stime = qtime.toString(Qt::LocalDate);
	ui->lblClock->setText(stime);

	// gebe akt. Netzwerkwerte aus
	bool online = this->fillNetworkLabels();
	if (online) {
		ui->lblNetworkStatus->setText(LABEL_NETWORK_ONLINE);
	} else {
		ui->lblNetworkStatus->setText(LABEL_NETWORK_OFFLINE);
	}
}

//
// fill widgets with correct texts
// use bash scripts --> easy applicable to different systems (just modify the scripts)
void MainWindow::fillWidgetsTexts() {
    // login button
    ui->btnCitrix->setText(BTN_CITRIX);
    ui->btnCitrix->setToolTip(BTN_CITRIX_TOOLTIP);

    // Network labels
    ui->grpBoxNetwork->setTitle(GRP_BOX_NETWORK); // grpBoxNetwork
    ui->lblNetworkStatus->setText(LABEL_NETWORK_ONLINE); // label network status
    ui->lblIpText->setText(LABEL_IP); // label IP
    ui->lblNetmaskText->setText(LABEL_NETMASK); // label NETMASK
    ui->lblGatewayText->setText(LABEL_GATEWAY); // label GATEWAY
    ui->lblTypeText->setText(LABEL_TYPE); // label TYPE

    // status and debug label
    ui->lblStatusLine->setText(""); // empty label STATUSLINE
    ui->lblDebugLine->setText(""); // empty label DEBUGLINE

    // fill network labels
    this->fillNetworkLabels();
}


//
// fill network labels
//
// @return: true=network connected, false=offline
bool MainWindow::fillNetworkLabels() {
	bool returnval = true; // if connected, return true

	// IP
    QString ip = exec_cmd_process_re_QString(init.get_script_ip());
    ui->lblIp->setText(ip);
	// NETMASK
    QString netmask = exec_cmd_process_re_QString(init.get_script_netmask());
    ui->lblNetmask->setText(netmask);

	// GATEWAY
    QString gateway = exec_cmd_process_re_QString(init.get_script_gateway());
    ui->lblGateway->setText(gateway);

	// TYPE
    QString type = init.get_network_type();
    ui->lblType->setText(type);

	return returnval;
}

