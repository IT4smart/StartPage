#include "startpage.h"
#include "ui_startpage.h"
#include "storebrowse.h"
#include <QDebug>
#include <QSettings>
#include <QTime>
#include <QFile>
#include <QProcess>
#include <QApplication>
#include <QWindow>
#include <QMessageBox>
#include <QIcon>
#include <QMapIterator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <chrono>
#include <thread>
#include <QLineEdit>
#include <QKeyEvent>


/*
 * Constructor
 */
StartPage::StartPage(QWidget *parent) : QMainWindow(parent), ui(new Ui::StartPage) {
    // tests --> delete later
    // doTests();

    // check if settings file exists
    if (!QFile(SETTINGS_PATH).exists()) {
        qDebug() << "File does not exist";
        startConfigPage(); // start ConfigPage and kill StartPage
    }

    // setup ui
    ui->setupUi(this);

    // set button flag to firstclick (0) --> so second click can be ignored
    mouseClickCount = 0;

    // network manager to check online state
    nwManager = new QNetworkConfigurationManager(this);
    connect(nwManager, &QNetworkConfigurationManager::onlineStateChanged, this, &StartPage::changeNetworkLogo);

    // change network logo
    this->changeNetworkLogo();

    // start clock
    QTime qtime = QTime::currentTime(); // read timer
    QDate qdate = QDate::currentDate();
    QString stime = qtime.toString(Qt::LocalDate);// convert timer to string
    QString sdate = qdate.longDayName(qdate.dayOfWeek()) // convert date to string
            + "\n" + qdate.toString(Qt::LocalDate);
    ui->lblClock->setText(stime+"\n"+sdate); // set label
    startTimer(2000); // set interrupt timer --> 2000 = 2 seconds

    // connect text changes
    connect(this->ui->leUser, &QLineEdit::textChanged, this, &StartPage::on_leUser_TextChanged);
    this->isFirstChange = true;
}

/*
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

}


/*
 * change network logo
 */
void StartPage::changeNetworkLogo() {
    // change network logo
    if (this->getNetworkStatus()) {
        ui->tbtnNetStatus->setText("online");
        ui->tbtnNetStatus->setIcon(QIcon(":/net_online.png"));
    } else {
        ui->tbtnNetStatus->setText("offline");
        ui->tbtnNetStatus->setIcon(QIcon(":/net_offline.png"));
    }

}

/*
 * init screen
 */
void StartPage::init_screen(int screen_w, int screen_h) {

    // save screen resolution
    screen_res_w = screen_w;
    screen_res_h = screen_h;

    // background color
    QPalette pal; // color palette
    pal.setColor(QPalette::Background, QColor(50,150,250)); // set background color
    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(pal); // add palette to label

    // position layout container
    int layoutc_w = screen_w; // width of message
    int layoutc_h = 0.6 * screen_h; // height of message
    int layoutc_offset_w = 0; // pos of left top corner
    int layoutc_offset_h = 0.2 * screen_h; // pos of left top corner
    ui->lblLayoutContainer->setText("");
    ui->lblLayoutContainer->setGeometry(layoutc_offset_w, layoutc_offset_h, layoutc_w, layoutc_h);

    // position company logo
    QString logo_path = getSettingsValue(LOGO_PATH).toString();
    QPixmap imgLogo(logo_path);
    int logo_w = 0.15 * screen_w; // width of logo
    int logo_h = 0.15 * screen_h; // height of logo
    int logo_offset_w = 0.05 * screen_w; // pos of left top corner
    int logo_offset_h = 0.05 * screen_h; // pos of left top corner
    ui->lblLogo->setGeometry(logo_offset_w, logo_offset_h, logo_w, logo_h);
    ui->lblLogo->setPixmap(imgLogo.scaled(logo_w, logo_h, Qt::KeepAspectRatio, Qt::FastTransformation));

    // position clock and date
    int clock_w = 0.2 * screen_w; // width of clock
    int clock_h = 0.2 * screen_h; // height of clock
    int clock_offset_w = 0.05 * screen_w; // pos of left top corner
    int clock_offset_h = screen_h - 0.1*screen_h - clock_h; // pos of left top corner
    QFont font_clock; // font
    font_clock.setPointSize(0.03 * screen_h);
    ui->lblClock->setFont(font_clock);
    ui->lblClock->setGeometry(clock_offset_w, clock_offset_h, clock_w, clock_h);

    // position network status
    int netstatus_wh = 0.11 * screen_h; // width and height of tool button
    int netstatus_offset_w = screen_w - 0.05*screen_w - netstatus_wh; // pos of left top corner
    int netstatus_offset_h = screen_h - 0.1*screen_h - netstatus_wh; // pos of left top corner
    QFont font_netstatus;
    font_netstatus.setPointSize(0.015 * screen_h);
    //font_netstatus.setFamily("Helvetica [Cronyx]");
    ui->tbtnNetStatus->setFont(font_netstatus);
    ui->tbtnNetStatus->setCheckable(false);
    ui->tbtnNetStatus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtnNetStatus->setIconSize(QSize(0.7*netstatus_wh,0.7*netstatus_wh)); // icon size
    ui->tbtnNetStatus->setGeometry(netstatus_offset_w, netstatus_offset_h, netstatus_wh, netstatus_wh);

    // position login button
    int login_w = 0.1 * screen_w; // width of login button
    int login_h = 0.1 * screen_h; // height of login button
    int login_offset_w = (screen_w + 3*login_w)/2; // pos of left top corner
    int login_offset_h = (screen_h - login_h)/2; // pos of left top corner
    QFont font_login;
    font_login.setPointSize(0.02 * screen_h);
    ui->btnLogin->setFont(font_login);
    ui->btnLogin->setCheckable(false);
    ui->btnLogin->setText("anmelden"); // --> change text dynamically
    ui->btnLogin->setGeometry(login_offset_w, login_offset_h, login_w, login_h);
    ui->btnLogin->raise();
    // connect enter key at password line to signal clicked
    connect(ui->lePW, SIGNAL(returnPressed()),ui->btnLogin,SIGNAL(clicked()));

    // position line edits
    int leUser_w = 0.25 * screen_w; // widht of line edit User
    int leUser_h = 0.05 * screen_h; // height of line edit User
    int lePW_w = leUser_w; // same like line edit user
    int lePW_h = leUser_h; // same like line edit user
    int leUser_offset_w = (screen_w - 1*leUser_w)/2; // pos of left top corner
    int leUser_offset_h = login_offset_h - 0.25*leUser_h; // take same offset of login button
    int lePW_offset_w = leUser_offset_w; // take same offset of line edit user
    int lePW_offset_h = leUser_offset_h + 1.5 * lePW_h;
    ui->leUser->setGeometry(leUser_offset_w, leUser_offset_h, leUser_w, leUser_h); // set position
    ui->lePW->setGeometry(lePW_offset_w, lePW_offset_h, lePW_w, lePW_h); // set position
    QFont font_leLogin; // font
    font_leLogin.setPointSize(0.02 * screen_h);
    font_leLogin.setItalic(true); // information in italic
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Text,Qt::gray); // gray text
    ui->leUser->setPalette(*palette);
    ui->leUser->setFont(font_leLogin);
    ui->lePW->setFont(font_leLogin);
    ui->leUser->setText(LE_USER_TEXT); // information
    ui->leUser->setCursorPosition(0); // cursor in the beginning

    // position line edit labels
    int lblUser_w = 0.1 * screen_w;
    int lblUser_h = 0.05 * screen_h;
    int lblPW_w = lblUser_w; // same as lblUser
    int lblPW_h = lblUser_h; // same as lblUser
    int lblUser_offset_w = leUser_offset_w - lblUser_w; // pos of left top corner
    int lblUser_offset_h = leUser_offset_h;
    int lblPW_offset_w = lblUser_offset_w;
    int lblPW_offset_h = lblUser_offset_h + 1.5 * lblPW_h;
    ui->lblUser->setGeometry(lblUser_offset_w, lblUser_offset_h, lblUser_w, lblUser_h);
    ui->lblPW->setGeometry(lblPW_offset_w, lblPW_offset_h, lblPW_w, lblPW_h);
    QFont font_lblLogin; // font
    font_lblLogin.setPointSize(0.02 * screen_h);
    ui->lblUser->setFont(font_lblLogin);
    ui->lblPW->setFont(font_lblLogin);
    ui->lblUser->setText("Benutzer:");
    ui->lblPW->setText("Passwort:");

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
}

/*
 * start login citrix
 */
void StartPage::loginCitrix() {
//    qDebug() << "loginCitrix";

    // for safety reason: delete citrix login information beforehand
    QString command = PRG_KILLALL+" "+PROC_AUTHMANAGERDAEMON+" "+PROC_SERVICERECORD;
    QPair<QString,QString> ret_pair = this->exec_cmd_process(command);

    // setup storebrowse module with login data
    QString netscaler_url = getSettingsValue(NETSCALER_URL).toString(); // netscaler link
    QString store_url = getSettingsValue(STORE_URL).toString(); // store link
    QString citrix_domain = getSettingsValue(CITRIX_DOMAIN).toString(); // citrix domain

    // start storebrowse instance
    QString user = citrix_domain + "\\" + ui->leUser->text();
    QString pw = ui->lePW->text();
    this->storebrowse = new Storebrowse(netscaler_url, store_url, user, pw);

    // make desktop inresponsive --> visual feedback that sth is happening
    ui->centralwidget->setEnabled(false); // disable buttons
    ui->lblMessage->setVisible(true);
    ui->lblMessage->setText("... bitte warten ..."); // waiting message
    ui->centralwidget->repaint(); // repaint centralwidget (container)

    // determine the actual store
    QString actual_store = this->storebrowse->getActualStore(); // list store
    if (actual_store=="") { // is actual store empty?
        // add actual store to system
        this->storebrowse->addStore();
    } // *** WILL THAT REALLY HAPPEN ???

    // get desktop(s)
    QMap<QString,QString> desktops = this->storebrowse->getDesktops();
    if (desktops.size()==0) { // no desktops --> normal start again
        // show messagebox
        QMessageBox msgBox;
        QFont font;
        font.setPointSize(0.015*this->screen_res_h);
        msgBox.setWindowTitle("Verbindungsfehler");
        msgBox.setFont(font);
        msgBox.setText("Es ist kein Login möglich.\n\n"
                       "Bitte überprüfen Sie:\n"
                       "- Ihre Logindaten (wahrscheinlichster Grund)\n"
                       "- Kabelverbindung (muss online sein)\n\n"
                       "Wenn Sie diesen Fehler wiederholt erhalten,\ninformieren Sie bitte Ihren Administrator!\n");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();

        QPair<QString,QString> ret_pair = this->storebrowse->deleteCitrixAuthentication(); // delete citrix login information

        // make desktop responsive again --> for later
        ui->centralwidget->setEnabled(true); // enable container
        this->setLogin(true); // set login elements to visible
        ui->lblMessage->setText(""); // // enable message
        ui->lblMessage->setVisible(false);
        ui->centralwidget->repaint(); // repaint centralwidget (container)

    } else if (desktops.size()==1) { // just one desktop --> start
        // start desktop
        QPair<QString,QString> ret_pair = this->storebrowse->startDesktop(desktops.first());
        qDebug() << "re_pair msg:\n" << ret_pair.first << "\nerr:\n" <<ret_pair.second;
        if (ret_pair.second=="") { // no error
            // wait for 15 secs --> the buttons will work after 15 secs again (because of timing for login procedure)
            std::this_thread::sleep_for(std::chrono::milliseconds(15000));
        }
        ret_pair = this->storebrowse->deleteCitrixAuthentication(); // delete citrix login information

        // make desktop responsive again --> for later
        ui->centralwidget->setEnabled(true); // enable buttons
        this->setLogin(true); // set login elements to visible
        ui->lblMessage->setText(""); // // show now message
        ui->lblMessage->setVisible(false);
        ui->centralwidget->repaint(); // repaint centralwidget (container)

    } else { // more desktops --> show desktops
        // make desktop responsive again but hide login details
        ui->centralwidget->setEnabled(true); // enable buttons
        this->setLogin(false); // set login elements to invisible
        ui->lblMessage->setText("... bitte auswählen ..."); // show new message
        ui->lblMessage->setVisible(true);

        // determine max no. of apps/desktops --> max. number is 4 rows of desktop in correct resolution
        int btn_w = 0.13 * this->screen_res_w; // width of button
        int btn_h = 0.13 * this->screen_res_h; // height of button
        int max_btns_in_row = this->screen_res_w / (1.1*btn_w); // leave space between buttons
        int no_desktops = desktops.size(); // no. of desktops to show
        int no_rows = round(double(no_desktops)/double(max_btns_in_row)+double(0.49)); // determine no of needed rows
        int max_desktops = max_btns_in_row * 4;

        // is there enough space for all buttons?
        if (no_desktops>max_desktops) { // no --> show error!
            // show messagebox
            QMessageBox msgBox;
            QFont font;
            font.setPointSize(0.015 * this->screen_res_h);
            msgBox.setWindowTitle("Maximale Anzahl Buttons überschritten");
            msgBox.setFont(font);
            msgBox.setText("Es sind mehr Desktops zur Auswahl als in Ihrer Bildschirmauflösung angezeigt werden können.\n\n"
                           "Bitte erhöhen Sie Ihre Bildschirmauflösung oder informieren Sie bitte Ihren Administrator!\n");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();

            QPair<QString,QString> ret_pair = this->storebrowse->deleteCitrixAuthentication(); // delete citrix login information

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
                font_btn.setPointSize(0.015 * this->screen_res_h);
                btn->setFont(font_btn); // set font
                btn->setCheckable(false); // not selectable by tab
                btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // make button with text under icon
                btn->setText(i.key()); // set button text
                btn->setIcon(QIcon(":/desktop.png"));
                btn->setIconSize(QSize(0.7*btn_w,0.7*btn_h)); // icon size
                btn->setFixedSize(QSize(btn_w,btn_h));
                btn->raise(); // put button in foreground

                // store desktop keys/values in local list
                this->desktops_list.append(qMakePair(i.key(), i.value()));

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
    // wait for 1 Second --> no double clicks possible
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    this->mouseClickCount = 0; // react to mouse clicks again
}

/*
 * set login
 * true = enable, false = disable
 */
void StartPage::setLogin(bool enable) {
//    qDebug() << "setLogin";

    ui->lblUser->setVisible(enable);
    ui->lblUser->setDisabled(!enable); // labels User+PW visible
    ui->lblPW->setVisible(enable);
    ui->lblPW->setDisabled(!enable);
    ui->leUser->setVisible(enable);
    ui->leUser->setDisabled(!enable); // line edits User+PW visible
    ui->lePW->setVisible(enable);
    ui->lePW->setDisabled(!enable);
    ui->btnLogin->setVisible(enable);
    ui->btnLogin->setDisabled(!enable); // login button visible
    QFont tmpFont = ui->leUser->font();
    tmpFont.setItalic(true);
    ui->leUser->setFont(tmpFont);
    QPalette tmpPalette = ui->leUser->palette();
    tmpPalette.setColor(QPalette::Text,Qt::gray); // gray text
    ui->leUser->setPalette(tmpPalette);
    ui->leUser->setText(LE_USER_TEXT); // show initial login text
    ui->leUser->setCursorPosition(0); // cursor in the beginning
    ui->lePW->setText("");
    this->isFirstChange = true; // react again on first entry in leUser ...

}

/*
 * start ConfigPage and kill StartPage
 */
void StartPage::startConfigPage() {

    // create the new process (ConfigPage)
    qDebug() << "starting ...";
    QProcess *process = new QProcess();
    process->startDetached("/bin/sh", QStringList{PRG_CONFIG_PAGE});
    process->waitForFinished();

    // killing actual process (StartPage)
    qDebug() << "killing ..." << qApp->applicationFilePath();
    qint64 pid = QCoreApplication::applicationPid();
    QProcess::startDetached("kill -SIGTERM " + QString::number(pid));
    //this->~StartPage();

}


/***************************
 * SLOTS
 ***************************/

/*void on_MouseDoubleClick() {
    qDebug() << "on_MouseDoubleClick";
}
*/


/*
 * on_btnLogin_clicked
 */
void StartPage::on_btnLogin_clicked() {
    mouseClickCount++; // increment mouse click
    qDebug() << "on_btnLogin_clicked:" << mouseClickCount;
    // MAKE IT ONLY CLICKABLE ONCE !!!
    if (mouseClickCount == 1) { // check if button was clicked first or second time (-> ignore double clicks)
        // first button click
        this->loginCitrix(); // start citrix login // ODER RDP LATER ...
    }


    //  use ...:  const QString CITRIX_RDP_TYPE = "global/citrix_rdp_type"
 /*   if (init.get_citrix_rdp_type()=="citrix") {
        // save citrix class
        this->ctx = new Citrix(init.get_citrix_url(), init.get_citrix_store()); // constructor
        startLoginCitrix(); // start_citrix

    } else {
        startLoginRdp(); // start rdp
    }
*/
}

/*
 * @brief StartPage::on_btnDesktop_clicked
 * @param index
 */
void StartPage::on_btnDesktop_clicked(int index) {
    qDebug() << "*** on_btnDesktop_clicked: " << index;
    mouseClickCount++; // increase mouse count
    if (mouseClickCount==1) { // only react on 1 cklick --> ignore double click
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
        QPair<QString,QString> ret_pair = this->storebrowse->startDesktop(desktop_chosen.second);
        if (ret_pair.second=="") { // no error
            // wait for 10 secs --> the buttons will work after 10 secs again (because of timing for login procedure)
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        } else if (ret_pair.second.contains("ServerLaunchFailure")) { // error desktop cant be started
            // show messagebox
            QMessageBox msgBox;
            QFont font;
            font.setPointSize(0.015 * this->screen_res_h);
            msgBox.setWindowTitle("Desktop Fehler");
            msgBox.setFont(font);
            msgBox.setText("Der ausgewählte Desktop kann nicht gestartet werden. Vermutlich sind die Citrix Studio Einstellungen falsch.\n\n"
                           "Bitte informieren Sie Ihren Administrator!\n");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();

        }

        ret_pair = this->storebrowse->deleteCitrixAuthentication(); // delete citrix login information

        // make desktop responsive again --> for later
        ui->centralwidget->setEnabled(true); // enable login
        this->setLogin(true);
        this->mouseClickCount = 0; // set mouse count back
    }


}

/*
 * an_tbtnNetStatus
 */
void StartPage::on_tbtnNetStatus_clicked() {
    qDebug() << "on_tbtnNetStatus";

    // get network info
    QString ip = this->exec_cmd_process(PRINT_IP).first; // ip
    QString mask = "<offline>";
    QString gateway = "<offline>";
    QString type = this->getSettingsValue("network/type").toString(); // network type
    if (getNetworkStatus()) { // network is online
        mask = this->exec_cmd_process(PRINT_NETMASK).first; // netmask
        gateway = this->exec_cmd_process(PRINT_GATEWAY).first; // gateway
    } else { // network is offline
        ip = "<offline>";
    }

    // create messagebox
    QMessageBox msgBox;
    QFont font;
    font.setPointSize(0.015*this->screen_res_h);
    msgBox.setWindowTitle("Netzwerk Status");
    msgBox.setFont(font);
    msgBox.setText("IP-Adresse:\t"+ip+"\t\n"
                   +"Netzmaske:\t"+mask+"\t\n"
                   +"Gateway:\t"+gateway+"\t\n"
                   +"IP-Vergabe:\t"+type+"\t\n\n");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

}

/*
 * on_le_TextChanged
 */
void StartPage::on_leUser_TextChanged() {
    if (this->isFirstChange // only do it with first change
        &&  (this->ui->leUser->text().length() == LE_USER_TEXT.length()+1)) // if just one piece was entered
    {
        QString tmpText = this->ui->leUser->text().at(0); // store first letter
        this->ui->leUser->setText(tmpText); // put the first letter back in
        this->isFirstChange = false; // ignore later changes
        QFont tmpFont = this->ui->leUser->font();// no more italic font
        tmpFont.setItalic(false);
        this->ui->leUser->setFont(tmpFont);
        QPalette tmpPalette = this->ui->leUser->palette(); // change textcolor to black
        tmpPalette.setColor(QPalette::Text, Qt::black);
        this->ui->leUser->setPalette(tmpPalette);
    }
}


/***************************
 * SUPPORTING FUNCTIONS
 ***************************/

/*
 * get Settings Value from Settings Key
 */
QVariant StartPage::getSettingsValue(QString settingsKey) {
    QSettings settings(SETTINGS_PATH, QSettings::IniFormat);
    if (settings.contains(settingsKey)){
//        qDebug() << "Key exists";

        return settings.value(settingsKey);
    } else {
        qDebug() << "Key doesn't exist";

        // display QMessageBox
        QMessageBox msgBox;
        QFont font;
        font.setPointSize(0.015*screen_res_h);
        msgBox.setWindowTitle("fehlender Eintrag in Konfiguration");
        msgBox.setFont(font);
        msgBox.setText("Es fehlt ein Wert in der Konfiguration für den Schluessel\n\n<"
                       +settingsKey
                       +">\n\n\n"
                       +"Es wird die Konfigurationsseite aufgerufen!\n\n");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();

        startConfigPage(); // start ConfigPage and kill StartPage
        return ""; // won't be reached since startConfigPage() will kill this instance
    }
}

/*
 * StartPage::getNetworkStatus
 * true=network connected, false=offline
 */
bool StartPage::getNetworkStatus() {
    return this->nwManager->isOnline(); // use network manager to get status
}

/*
 * Desctructor
 */
StartPage::~StartPage() {
    delete ui;
}

/*
 * run system command via QProcess and read out stdout and stderror
 * @return  QPair of <QString,QString> (= <buffer_result,buffer_error>)
 */
QPair<QString,QString> StartPage::exec_cmd_process(QString command) {
    QPair<QString,QString> ret_pair; // initiate return pair of <QByteArray,QByteArray>

    // start process for citrix
    QProcess *process = new QProcess();
    process->start(PRG_SHELL);
    process->write(command.toLatin1());
    process->closeWriteChannel();

    // get buffer and buffer_error
    QByteArray buffer;
    QByteArray buffer_error;
    while(process->waitForFinished()) {
        buffer.append(process->readAllStandardOutput());
        buffer_error.append(process->readAllStandardError());
    }

    process->close(); // close citrix process

    // return the QPair
    ret_pair.first = buffer.data(); // normal stream
    ret_pair.second = buffer_error.data(); // error stream
    return ret_pair;
}

/*
 * Tests
 */
void StartPage::doTests() {
    qDebug() << "TEST!";
//    QSettings settings(SETTINGS_PATH, QSettings::IniFormat);

    // global settings
/*    settings.setValue("global/logo_path", "../Ressources/ass-logo.png");
    settings.setValue("global/citrix_rdp_type", "citrix");

    // citrix settings
    settings.setValue("citrix/store", "https://ddcxd1.ass-hn.de/citrix/xdstore/discovery");
    settings.setValue("citrix/url", "https://extern.ass-hn.de");

    // rdp settings
    settings.setValue("rdp/domain", "Domain.local");
    settings.setValue("rdp/server", "https://server.domain.de");

    // network settings
    settings.setValue("network/type", "dhcp");
    settings.setValue("network/gateway", "192.168.152.2");
    settings.setValue("network/ip", "192.168.152.129");
    settings.setValue("network/netmask", "255.255.255.0");

    // write to file SETTINGS_PATH
    settings.sync();
*/
    // get settings test
//    qDebug() << "size=" << settings.childGroups().size();



}

