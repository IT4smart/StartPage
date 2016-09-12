#ifndef RDP_H
#define RDP_H

#include <QString>
#include <QDebug>
#include <QProcess>
#include <stdio.h>
#include <stdlib.h>


const QString PRG_RDP = "/usr/bin/xfreerdp";
const QString PAR_NOCERT = "/cert-ignore";
const QString PAR_FULLSCREEN = "/f";
const QString PAR_USER = "/u:";
const QString PAR_PW = "/p:";
const QString PAR_DOMAIN = "/d:";
const QString PAR_SERVER = "/v:";

class Rdp : public QObject {
    Q_OBJECT

    public:
        // methods
        Rdp(QString user, QString password, QString domain, QString server, QString rdp_extraflag);
        ~Rdp();
        void startRdp(); // start remote desktop
        QProcess process;

    private:
        // vars
        QString user; //std::string user;
        QString password; //std::string password;
        QString domain; //std::string domain;
        QString server; //std::string server;
        QString extraflag;

   public slots:
        void process_started();
        void processError(QProcess::ProcessError err);
        void processErrorStream();
        void processFinished(int exitcode, QProcess::ExitStatus exitstatus);

};

#endif // RDP_H
