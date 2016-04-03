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
#include <QMovie>
#include <QMap>
#include <chrono>
#include <thread>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMapIterator>
#include <math.h>
#include <QSignalMapper>

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
    int netstatus_wh = 0.11 * screen_h; // width and height of tool button
    int netstatus_offset_w = screen_w - 0.05*screen_w - netstatus_wh; // pos of left top corner
    int netstatus_offset_h = screen_h - 0.1*screen_h - netstatus_wh; // pos of left top corner
    QFont font_netstatus;
    font_netstatus.setPointSize(0.01 * screen_h);
    //font_netstatus.setFamily("Helvetica [Cronyx]");
    ui->tbtnNetStatus->setFont(font_netstatus);
    ui->tbtnNetStatus->setCheckable(false);
    ui->tbtnNetStatus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtnNetStatus->setIconSize(QSize(0.7*netstatus_wh,0.7*netstatus_wh)); // icon size
    ui->tbtnNetStatus->setGeometry(netstatus_offset_w, netstatus_offset_h, netstatus_wh, netstatus_wh);

    // position login button
    int login_w = 0.1 * screen_w; // width of login button
    int login_h = 0.15 * screen_h; // height of login button
    int login_offset_w = (screen_w - login_w)/2; // pos of left top corner
    int login_offset_h = (screen_h - login_h)/2; // pos of left top corner
    QFont font_login;
    font_login.setPointSize(0.015 * screen_h);
    ui->tbtnLogin->setFont(font_login);
    ui->tbtnLogin->setCheckable(false);
    ui->tbtnLogin->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtnLogin->setText("anmelden"); // --> change text dynamically
    if (init.get_citrix_rdp_type()=="citrix") {
        ui->tbtnLogin->setIcon(QIcon(":/citrix.png")); //--> change icon dynamically
    } else {
        ui->tbtnLogin->setIcon(QIcon(":/rdp_ms.png")); //--> change icon dynamically
    }
    ui->tbtnLogin->setIconSize(QSize(0.7*login_w,0.7*login_h)); // icon size
    ui->tbtnLogin->setGeometry(login_offset_w, login_offset_h, login_w, login_h);
    ui->tbtnLogin->raise();

    // position message
    int msg_w = 0.3 * screen_w; // width of message
    int msg_h = 0.1 * screen_h; // height of message
    int msg_offset_w = (screen_w - msg_w)/2; // pos of left top corner
    int msg_offset_h = screen_h - 2*msg_h; // pos of left top corner
    QFont font_msg; // font
    font_msg.setPointSize(0.02 * screen_h);
    ui->lblMessage->setText("");
    ui->lblMessage->setFont(font_msg);
    ui->lblMessage->setGeometry(msg_offset_w, msg_offset_h, msg_w, msg_h);

    // position layout container
    int layoutc_w = screen_w; // width of message
    int layoutc_h = 0.6 * screen_h; // height of message
    int layoutc_offset_w = 0; // pos of left top corner
    int layoutc_offset_h = 0.2 * screen_h; // pos of left top corner
    ui->lblLayoutContainer->setText("");
    ui->lblLayoutContainer->setGeometry(layoutc_offset_w, layoutc_offset_h, layoutc_w, layoutc_h);

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
    msgBox.setText("IP-Adresse:\t"+ip+"\t\n"
                   +"Netzmaske:\t"+mask+"\t\n"
                   +"Gateway:\t"+gateway+"\t\n"
                   +"IP-Vergabe:\t"+type+"\t\n\n");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

/**
 * @brief on_tbtnLogin_clicked
 */
void StartPage::on_tbtnLogin_clicked() {
    if (init.get_citrix_rdp_type()=="citrix") {
        // save citrix class
        this->ctx = new Citrix(init.get_citrix_url(), init.get_citrix_store()); // constructor
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

    // delete user credentials
    QPair<QString,QString> ret_pair = ctx->deleteCitrixAuthentication(); // delete citrix login information

    // is netscaler link and store empty???
//    if (true) { // netscaler link and store are empty
    if (this->init.get_citrix_url()=="" && this->init.get_citrix_store()=="") { // netscaler link and store are empty
        // show messagebox
        QMessageBox msgBox;
        QFont font;
        font.setPointSize(0.015*this->get_screen_res_h());
        msgBox.setWindowTitle("Verbindungsfehler");
        msgBox.setFont(font);
        msgBox.setText("Es ist keine Verbindung zum Citrix Store möglich. "
                       "Die Citrix Netscaler- und Storeadresse sind leer!\n\n"
                       "Bitte geben Sie diese in der Konfigurationsseite ein.\n\n"
                       "Wenn Sie nicht weiter wissen, informieren Sie bitte Ihren Administrator!\n");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();

//        this->startConfigPage();

    } else { // continue
        // make desktop inresponsive
        ui->centralwidget->setEnabled(false); // disable buttons
        ui->lblMessage->setVisible(true);
        ui->lblMessage->setText("... bitte warten ..."); // waiting message
        ui->centralwidget->repaint(); // repaint centralwidget (container)

        // determine the actual store
        QString actual_store = ctx->getActualStore(); // list store
        if (actual_store=="") { // is actual store empty?
            // add actual store to system --> login will appear
            ctx->addStore();
        }

        // get desktop(s)
        QMap<QString,QString> desktops = ctx->getDesktops();
//for (int i=0;i<20;i++) { // TEST mit multi desktops
//    desktops.insert("key" +QString::number(i),"link");
//}
        if (desktops.size()==0) { // no desktops --> normal start again
            // show messagebox
            QMessageBox msgBox;
            QFont font;
            font.setPointSize(0.015*this->get_screen_res_h());
            msgBox.setWindowTitle("Verbindungsfehler");
            msgBox.setFont(font);
            msgBox.setText("Es ist keine Verbindung zum Citrix Store möglich.\n\n"
                           "Bitte überprüfen Sie die:\n"
                           "- Kabel-/WLAN-Verbindung\n"
                           "- Citrixstore-Adresse\n"
                           "- externe Gateway Adresse\n\n"
                           "Wenn Sie nicht weiter wissen, informieren Sie bitte Ihren Administrator!\n");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();

            // make desktop responsive again --> for later
            ui->centralwidget->setEnabled(true); // disable buttons
            ui->tbtnLogin->setDisabled(false); // login button visible
            ui->tbtnLogin->setVisible(true);
            ui->lblMessage->setText(""); // // show now message
            ui->lblMessage->setVisible(false);
            ui->centralwidget->repaint(); // repaint centralwidget (container)

        } else if (desktops.size()==1) { // just one desktop --> start
            // start desktop
            QPair<QString,QString> ret_pair = this->ctx->startDesktop(desktops.first());
            qDebug() << "re_pair msg:\n" << ret_pair.first << "\nerr:\n" <<ret_pair.second;
            if (ret_pair.second=="") { // no error
                // wait for 15 secs --> the buttons will work after 15 secs again (because of timing for login procedure)
                std::this_thread::sleep_for(std::chrono::milliseconds(15000));
            }

            // make desktop responsive again --> for later
            ui->centralwidget->setEnabled(true); // enable buttons
            ui->tbtnLogin->setDisabled(false); // login button visible
            ui->tbtnLogin->setVisible(true);
            ui->lblMessage->setText(""); // // show now message
            ui->lblMessage->setVisible(false);
            ui->centralwidget->repaint(); // repaint centralwidget (container)

        } else { // more desktops --> show desktops
            // make desktop responsive again
            ui->centralwidget->setEnabled(true); // enable buttons
            ui->tbtnLogin->setDisabled(true); // login button invisible
            ui->tbtnLogin->setVisible(false);
            ui->lblMessage->setText("... bitte auswählen ..."); // // show new message
            ui->lblMessage->setVisible(true);

            // determine max no. of apps/desktops --> max. number is 4 rows of desktop in correct resolution
            int btn_w = 0.13 * this->get_screen_res_w(); // width of button
            int btn_h = 0.13 * this->get_screen_res_h(); // height of button
            int max_btns_in_row = this->screen_res_w / (1.1*btn_w); // leave space between buttons
            int no_desktops = desktops.size(); // no. of desktops to show
            int no_rows = round(double(no_desktops)/double(max_btns_in_row)+double(0.49)); // determine no of needed rows
            int max_desktops = max_btns_in_row * 4;
            qDebug() << "max btns per row:" << max_btns_in_row << " needed rows:" << no_rows;

            // is there enough space for all buttons?
            if (no_desktops>max_desktops) { // no --> show error!
                // show messagebox
                QMessageBox msgBox;
                QFont font;
                font.setPointSize(0.015 * this->get_screen_res_h());
                msgBox.setWindowTitle("Maximale Anzahl Buttons überschritten");
                msgBox.setFont(font);
                msgBox.setText("Es sind mehr Desktops zur Auswahl als in Ihrer Bildschirmauflösung angezeigt werden können.\n\n"
                               "Bitte erhöhen Sie Ihre Bildschirmauflösung oder informieren Sie bitte Ihren Administrator!\n");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.exec();

            } else { // yes --> show buttons
                // create layouts
                this->ctx_desktop_v_layout = new QVBoxLayout(ui->lblLayoutContainer); // create QVBoxLayout
                QList<QHBoxLayout*> h_layout_list;
                for (int i=0;i<no_rows;i++) { // create all needed rows
                    QHBoxLayout *h_layout = new QHBoxLayout;//create QHBoxLayout
                    this->ctx_desktop_v_layout->addLayout(h_layout);
                    h_layout_list.append(h_layout); // append QHBoxLayout to QVBoxLayout
                }

                QMapIterator<QString,QString> i(desktops); // iterator for map
                int row_act; // actual row to put in button
                int desktop_nr = 1; // actual desktop number
                this->signalMapper = new QSignalMapper(this); // signal mapper zur übergabe von daten von signals to slots
                while (i.hasNext()) {
                    i.next(); // get next map element

                    // create buttons
                    QToolButton *btn = new QToolButton;
                    QFont font_btn; // font and size
                    font_btn.setPointSize(0.02 * this->screen_res_h);
                    btn->setFont(font_btn); // set font
                    btn->setCheckable(false); // not selectable by tab
                    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // make button with text under icon
                    btn->setText(i.key()); // set button text
                    btn->setIcon(QIcon(":/desktop.png"));
                    btn->setIconSize(QSize(0.7*btn_w,0.7*btn_h)); // icon size
                    btn->setFixedSize(QSize(btn_w,btn_h));
                    btn->raise(); // put button in foreground

                    // store desktop keys/values in local list
                    desktops_list.append(qMakePair(i.key(), i.value()));

                    // add button to layout
                    row_act = std::max(round(double(desktop_nr)/double(max_btns_in_row)+double(0.49))-1.0,0.0);
                    h_layout_list.at(row_act)->addWidget(btn);

                    // add signals to slot
                    this->signalMapper->setMapping(btn, desktop_nr); // setze mapper
                    connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map())); // connect btn to slot map

                    desktop_nr++; // increase desktop number

                }

                // connect signalmapper to slot
                connect(this->signalMapper, SIGNAL(mapped(int)), this, SLOT(on_btnDesktop_clicked(int)));
            }
        }
    }
}


/**
 * @brief StartPage::on_btnDesktop_clicked
 * @param index
 */
void StartPage::on_btnDesktop_clicked(int index) {
    qDebug() << "*** on_btnDesktop_clicked: " << index;
    QPair<QString,QString> desktop_chosen = desktops_list.at(index-1);
    QString link_chosen = desktop_chosen.second;

    // delete all desktop layout elements
    QObjectList childrenList = ui->lblLayoutContainer->children();
    QToolButton *btn_chosen; // store chosen button to delete later
    for (int i=0;i<childrenList.size();i++) {
        QString cname = childrenList.at(i)->metaObject()->className();
//        qDebug() << "child" << i << ": class=" << cname;
        if (cname=="QToolButton") { // hide and delete all buttons
            QToolButton *temp = qobject_cast<QToolButton *>(childrenList.at(i));
            temp->hide(); // hide
            temp->disconnect(); // disconnect from signals
            temp->deleteLater(); // finally delete object
        } else if (cname=="QVBoxLayout") { // hide and delete all layouts
            QVBoxLayout *temp = qobject_cast<QVBoxLayout *>(childrenList.at(i));
            temp->disconnect(); // disconnect from signals
            temp->deleteLater(); // finally delete object
        }
    }

    // delete desktop list
    desktops_list.empty();

    // change ui
    ui->centralwidget->setEnabled(false); // disable screen
    ui->lblMessage->setText("... bitte warten ..."); // // show new message
    ui->lblMessage->setVisible(true);
    ui->centralwidget->repaint();

    // start chosen desktop
    QPair<QString,QString> ret_pair = this->ctx->startDesktop(desktop_chosen.second);
    if (ret_pair.second=="") { // no error
        // wait for 15 secs --> the buttons will work after 15 secs again (because of timing for login procedure)
        std::this_thread::sleep_for(std::chrono::milliseconds(15000));
    } else if (ret_pair.second.contains("ServerLaunchFailure")) { // error desktop cant be started
        // show messagebox
        QMessageBox msgBox;
        QFont font;
        font.setPointSize(0.015 * this->get_screen_res_h());
        msgBox.setWindowTitle("Desktop Fehler");
        msgBox.setFont(font);
        msgBox.setText("Der ausgewählte Desktop kann nicht gestartet werden. Vermutlich sind die Citrix Studio Einstellungen falsch.\n\n"
                       "Bitte informieren Sie Ihren Administrator!\n");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();

    }

    // make desktop responsive again --> for later
    ui->centralwidget->setEnabled(true); // enable buttons
    ui->tbtnLogin->setDisabled(false); // login button visible
    ui->tbtnLogin->setVisible(true);
    ui->tbtnLogin->raise(); // put button in foreground
    ui->lblMessage->setText(""); // // show now message
    ui->lblMessage->setVisible(false);
    ui->centralwidget->repaint(); // repaint centralwidget (container)

}



/**
 * @brief StartPage::startLoginRdp
 */
void StartPage::startLoginRdp() {
    qDebug() << "startLoginRdp";
}


/**
 * @brief StartPage::startConfigPage
 */
void StartPage::startConfigPage() {
    qDebug() << "startConfigPage";
    QString command = "sudo ../../configurationpage/ConfigPage/ConfigPage";
    QPair<QString,QString> pair = exec_cmd_process(command); // returns result and error as QPair
    QString result = pair.first;
    QString error = pair.second;
    qDebug() << "result:\n" << result << "\nerror:\n" << error;
}
