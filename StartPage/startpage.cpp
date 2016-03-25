#include "startpage.h"
#include "ui_startpage.h"
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
#include <QMessageBox>
#include <QDate>
#include <QString>

/**
 * constructor
 * @brief StartPage::StartPage
 * @param parent
 */
StartPage::StartPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartPage),
    init("empty")
{
    // setup ui
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
    QTime qtime = QTime::currentTime(); // read timer
    QDate qdate = QDate::currentDate();
    QString stime = qtime.toString(Qt::LocalDate);// convert timer to string
    QString sdate = qdate.longDayName(qdate.dayOfWeek()) // convert date to string
            + "\n" + qdate.toString(Qt::LocalDate);
    ui->lblClock->setText(stime+"\n"+sdate); // set label
    startTimer(1000); // set interrupt timer --> 1000 = 1 second

    // get network status
    bool online = this->getNetworkStatus();

    // change network logo
    if (online) {
        ui->tbtnNetStatus->setText("online");
        ui->tbtnNetStatus->setIcon(QIcon(":/net_online.png"));
    } else {
        ui->tbtnNetStatus->setText("offline");
        ui->tbtnNetStatus->setIcon(QIcon(":/net_offline.png"));
    }
}

/**
 * destructor
 * @brief StartPage::~StartPage
 */
StartPage::~StartPage() {
    delete ui;
}

/**
 * @brief StartPage::timerEvent
 * @param event
 */
void StartPage::timerEvent(QTimerEvent *event) {
    //TODO
    (void) event;

    // show time
    QTime qtime = QTime::currentTime();
    QDate qdate = QDate::currentDate();
    QString stime = qtime.toString(Qt::LocalDate);
    QString sdate = qdate.longDayName(qdate.dayOfWeek()) + "\n" + qdate.toString(Qt::LocalDate);
    ui->lblClock->setText(stime+"\n"+sdate);

    // get network status
    bool online = this->getNetworkStatus();

    // change network logo
    if (online) {
        ui->tbtnNetStatus->setText("online");
        ui->tbtnNetStatus->setIcon(QIcon(":/net_online.png"));
    } else {
        ui->tbtnNetStatus->setText("offline");
        ui->tbtnNetStatus->setIcon(QIcon(":/net_offline.png"));
    }
}


/** @brief init_screen
 * @param x
 * @param y
 */
void StartPage::init_screen(int screen_w, int screen_h) {
    // save screen resolution
    screen_res_w = screen_w;
    screen_res_h = screen_h;

    // position company logo
    QString logo_path = init.get_client_logo();
    QPixmap imgLogo(logo_path);
    int logo_w = 0.1 * screen_w; // width of logo
    int logo_h = 0.1 * screen_h; // height of logo
    int logo_offset_w = 0.05 * screen_w; // pos of left top corner
    int logo_offset_h = 0.05 * screen_h; // pos of left top corner
    ui->lblLogo->setGeometry(logo_offset_w, logo_offset_h, logo_w, logo_h);
    ui->lblLogo->setPixmap(imgLogo.scaled(logo_w, logo_h, Qt::KeepAspectRatio, Qt::FastTransformation));

    // position clock and date
    int clock_w = 0.15 * screen_w; // width of clock
    int clock_h = 0.15 * screen_h; // height of clock
    int clock_offset_w = 0.05 * screen_w; // pos of left top corner
    int clock_offset_h = screen_h - 0.1*screen_h - clock_h; // pos of left top corner
    QFont font_clock; // font
    font_clock.setPointSize(0.02 * screen_h);
    ui->lblClock->setFont(font_clock);
    ui->lblClock->setGeometry(clock_offset_w, clock_offset_h, clock_w, clock_h);

    // position network status
    int netstatus_wh = 0.1 * screen_h; // width and height of tool button
    int netstatus_offset_w = screen_w - 0.05*screen_w - netstatus_wh; // pos of left top corner
    int netstatus_offset_h = screen_h - 0.1*screen_h - netstatus_wh; // pos of left top corner
    QFont font_netstatus;
    font_netstatus.setPointSize(0.015 * screen_h);
    ui->tbtnNetStatus->setFont(font_netstatus);
    ui->tbtnNetStatus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //    ui->tbtnNetStatus->setText("online"); --> change text dynamically
    //    ui->tbtnNetStatus->setIcon(QIcon(":/net_online.png")); --> change icon dynamically
    ui->tbtnNetStatus->setIconSize(QSize(0.7*netstatus_wh,0.7*netstatus_wh)); // icon size
    ui->tbtnNetStatus->setGeometry(netstatus_offset_w, netstatus_offset_h, netstatus_wh, netstatus_wh);

    // position login button
    int login_w = 0.1 * screen_w; // width of tool button
    int login_h = 0.125 * screen_h; // height of tool button
    int login_offset_w = (screen_w - login_w)/2; // pos of left top corner
    int login_offset_h = (screen_h - login_h)/2; // pos of left top corner
    QFont font_login;
    font_login.setPointSize(0.02 * screen_h);
    ui->tbtnLogin->setFont(font_login);
    ui->tbtnLogin->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtnLogin->setText("anmelden"); // --> change text dynamically
    if (init.get_citrix_rdp_type()=="citrix") {
        ui->tbtnLogin->setIcon(QIcon(":/citrix.png")); //--> change icon dynamically
    } else {
        ui->tbtnLogin->setIcon(QIcon(":/rdp_ms.png")); //--> change icon dynamically
    }
    ui->tbtnLogin->setIconSize(QSize(0.7*login_w,0.7*login_h)); // icon size
    ui->tbtnLogin->setGeometry(login_offset_w, login_offset_h, login_w, login_h);
}

/**
 * @brief StartPage::get_screen_res_w
 * @return
 */
int StartPage::get_screen_res_w() {
    return screen_res_w;
}

/**
 * @brief StartPage::get_screen_res_h
 * @return
 */
int StartPage::get_screen_res_h() {
    return screen_res_h;
}


/**
 * @brief StartPage::getNetworkStatus
 * @return true=network connected, false=offline
 */
bool StartPage::getNetworkStatus() {
    bool returnval = true; // if connected, return true
    QString ip = exec_cmd_process_re_QString(init.get_script_ip()); // get ip

    if (ip=="") { returnval=false; } // if empty ip -> return false
    return returnval;
}

/**
 * @brief StartPage::on_tbtnNetStatus_clicked
 */
void StartPage::on_tbtnNetStatus_clicked() {
    // get network info
    QString ip = exec_cmd_process_re_QString(init.get_script_ip()); // ip
    QString mask = "<offline>";
    QString gateway = "<offline>";
    QString type = init.get_network_type(); // network type
    if (getNetworkStatus()) { // network is online
        mask = exec_cmd_process_re_QString(init.get_script_netmask()); // netmask
        gateway = exec_cmd_process_re_QString(init.get_script_gateway()); // gateway
    } else { // network is offline
        ip = "<offline>";
    }

    // create messagebox
    QMessageBox msgBox;
    QFont font;
    font.setPointSize(0.015*this->get_screen_res_h());
    msgBox.setWindowTitle("Netzwerk Status");
    msgBox.setFont(font);
    msgBox.setText("IP-Adresse:\t"+ip+"\n"
                   +"Netzmaske:\t"+mask+"\n"
                   +"Gateway:\t"+gateway+"\n"
                   +"IP-Vergabe:\t"+type);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

/**
 * @brief on_tbtnLogin_clicked
 */
void StartPage::on_tbtnLogin_clicked() {
    if (init.get_citrix_rdp_type()=="citrix") {
        startLoginCitrix(); // start_citrix
    } else {
        startLoginRdp(); // start rdp
    }

    // make tbtnLogin button visible again
}


/**
 * @brief StartPage::startLoginCitrix
 */
void StartPage::startLoginCitrix() {
    qDebug() << "startLoginCitrix";

    QString ctx_link = init.get_citrix_url();
    QString ctx_store = init.get_citrix_store();

    // link or store empty???

    Citrix *ctx = new Citrix(ctx_link, ctx_store); // constructor
    ui->centralwidget->setEnabled(false);
    ui->centralwidget->repaint();
    ctx->getDesktops();
//    Citrix::Citrix ctx = new Citrix::Citrix();
//    ctx.getDesktops();
}

/*    // baue neue Buttons auf
    signalMapper = new QSignalMapper(this); // signal mapper zur übergabe von daten von signals to slots
    for (int i=0;i<names.size();i++) {

        QToolButton *btn = new QToolButton(this);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setText(names.at(i));
        btn->setIconSize(QSize(96,96)); // icon size
        btn->setIcon(QIcon(":/Desktop.png"));
        // icon taken from: http://www.softicons.com/system-icons/hadaikum-icons-by-tiny-lab/desktop-icon
        btn->setFixedSize(150,150); // button size

//        btn->setPalette(QPalette(QColor(0,0,1))); // background color for button
//        btn->setAutoFillBackground(true);

/*        QPushButton *btn = new QPushButton(names.at(i)); // create button
        btn->setFont(QFont("Calibri", 26)); // set font
        ui->hLayoutElements->addWidget(btn); // add button to layout
        signalMapper->setMapping(btn, i); // setze mapper
        connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map())); // connect btn to slot map
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(on_btnDesktop_clicked(int)));
/*
}

/**
 * @brief StartPage::startLoginRdp
 */
void StartPage::startLoginRdp() {
    qDebug() << "startLoginRdp";
}
