#include "rdp.h"
#include "startpage.h"
#include "easylogging++.h"

/*
 * constructor Rdp
 */
Rdp::Rdp(QString user, QString password, QString domain, QString server) {
    // Set login variables
    this->user = user;//.toStdString();
    this->password = password;//.toStdString();
    this->domain = domain;//.toStdString();
    this->server = server;//.toStdString();

    SYSLOG(DEBUG) << "Set all informationen for a rdp session";
}

/*
 * desctructor
 */
Rdp::~Rdp() {
}

/*
 * start RDP session
 */
QPair<QString,QString> Rdp::startRdp() {

    QString command = PRG_RDP + " "
                        + PAR_NOCERT + " "
                        + PAR_FULLSCREEN + " "
                        + PAR_USER + this->user + " "
                        + PAR_PW + this->password + " "
                        + PAR_DOMAIN + this->domain + " "
                        + PAR_SERVER + this->server;
    QPair<QString,QString> ret_pair = StartPage::exec_cmd_process(command);
    SYSLOG(DEBUG) << "RDP command: " << command.toStdString();
    SYSLOG_IF(ret_pair.second != "", ERROR) << ret_pair.second.toStdString();

    return ret_pair; // return results (first: no error result, second: error result)
}

