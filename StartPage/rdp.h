#ifndef RDP_H
#define RDP_H

#include <QString>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>


const QString PRG_RDP = "/usr/bin/xfreerdp";
const QString PAR_NOCERT = "/cert-ignore";
const QString PAR_FULLSCREEN = "/f";
const QString PAR_USER = "/u:";
const QString PAR_PW = "/p:";
const QString PAR_DOMAIN = "/d:";
const QString PAR_SERVER = "/v:";

class Rdp : QObject {
    public:
        // methods
        Rdp(QString user, QString password, QString domain, QString server);
        ~Rdp();
        QPair<QString,QString> startRdp(); // start remote desktop

    private:
        // vars
        QString user; //std::string user;
        QString password; //std::string password;
        QString domain; //std::string domain;
        QString server; //std::string server;
};

#endif // RDP_H
