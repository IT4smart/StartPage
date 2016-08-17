#include "rdp.h"
#include "startpage.h"

/*
 * constructor Rdp
 */
Rdp::Rdp(QString user, QString password, QString domain, QString server) {
    // Set login variables
    this->user = user;//.toStdString();
    this->password = password;//.toStdString();
    this->domain = domain;//.toStdString();
    this->server = server;//.toStdString();
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
                        + PAR_USER + this->user + " "
                        + PAR_PW + this->password + " "
                        + PAR_DOMAIN + this->domain + " "
                        + PAR_SERVER + this->server;
    QPair<QString,QString> ret_pair = StartPage::exec_cmd_process(command);

    return ret_pair; // return results (first: no error result, second: error result)
}

