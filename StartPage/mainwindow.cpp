#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Citrix.h"
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
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // start clock
    QTime qtime = QTime::currentTime(); //Timer auslesen
    QString stime = qtime.toString(Qt::LocalDate);//Timerwert als String wandeln
    ui->lblClock->setText(stime);//Text von Label setzen
    startTimer(5000);

    // fill widgets with texts
    MainWindow::fillWidgetsTexts();

}

//
// destructor
//
MainWindow::~MainWindow() {
    delete ui;
}

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

//
// button Exit
void MainWindow::on_btnExit_clicked() {
    QApplication::exit();
}

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

//
// process timer event
//
void MainWindow::timerEvent(QTimerEvent *event) {
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
//
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
// return: true=network connected, false=offline
bool MainWindow::fillNetworkLabels() {
    bool returnval = true; // if connected, return true

    // IP
    QString program = SHELL_IP;
    QStringList arguments;
    procSystem = new QProcess(this);
    procSystem->start(program, arguments);
    procSystem->waitForFinished();
    QString output = procSystem->readAllStandardOutput();
    ui->lblIp->setText(output);
    if (output=="\n") { // if no ip --> offline, return false
        returnval = false;
    }

    // NETMASK
    program = SHELL_NETMASK;
    procSystem = new QProcess(this);
    procSystem->start(program, arguments);
    procSystem->waitForFinished();
    output = procSystem->readAllStandardOutput();
    ui->lblNetmask->setText(output);

    // GATEWAY
    program = SHELL_GATEWAY;
    procSystem = new QProcess(this);
    procSystem->start(program, arguments);
    procSystem->waitForFinished();
    output = procSystem->readAllStandardOutput();
    ui->lblGateway->setText(output);

    // TYPE

    return returnval;
}
