#include "rdp.h"
#include "startpage.h"
#include "easylogging++.h"
#include <QMessageBox>

/*
 * constructor Rdp
 */
Rdp::Rdp(QString user, QString password, QString domain, QString server) {
    // Set login variables
    this->user = user;//.toStdString();
    this->password = password;//.toStdString();
    this->domain = domain;//.toStdString();
    this->server = server;//.toStdString();

    QObject::connect(&process, SIGNAL(started()), this, SLOT(process_started()));
    QObject::connect(&process, SIGNAL(QProcess::ProcessError), this, SLOT(process_error(QProcess::ProcessError)));
    QObject::connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(processErrorStream()));
    QObject::connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));

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
void Rdp::startRdp() {

    QStringList arguments;
    arguments << PAR_NOCERT << PAR_FULLSCREEN << PAR_USER + this->user << PAR_PW + this->password << PAR_DOMAIN + this->domain << PAR_SERVER + this->server << "/sound:sys:pulse /rfx /fonts";

    SYSLOG(DEBUG) << "Start login for rdp session";
    process.start("xfreerdp", arguments);

}

/**
 * @brief Rdp::process_started
 */
void Rdp::process_started() {
    SYSLOG(DEBUG) << "Process for rdp connection started";
}

/**
 * @brief Rdp::processErrorStream
 */
void Rdp::processErrorStream() {
    process.setReadChannel(QProcess::StandardError);
    QByteArray buffer = process.readAllStandardError();

    SYSLOG(DEBUG) << buffer.data();

    if (buffer.toStdString().find("Authentication failure, check credentials") != std::string::npos) {
        QMessageBox::information(0, "Authentifizierungsfehler", "Falscher Benutzername oder Passwort");
        SYSLOG(ERROR) << "Authentification failure!";
    } else if(buffer.toStdString().find("getaddrinfo (System error)") != std::string::npos or buffer.toStdString().find("getaddrinfo: System error") != std::string::npos) {
        QMessageBox::information(0, "Verbindungsfehler", "Serverfehler, bitte konktaktieren Sie ihren Administrator.");
        SYSLOG(ERROR) << "Error connecting to server!";
    } else if(buffer.toStdString().find("getaddrinfo: System error") != std::string::npos or buffer.toStdString().find("getaddrinfo: System error") != std::string::npos) {
        QMessageBox::information(0, "Verbindungsfehler", "Serverfehler, bitte kontaktieren Sie ihren Administrator");
        SYSLOG(ERROR) << "Error connecting to server!";
    } else {
        SYSLOG(INFO) << "No errors during connection to server";
    }
}

/**
 * @brief Rdp::processFinished
 * @param exitcode
 * @param exitstatus
 */
void Rdp::processFinished(int exitcode, QProcess::ExitStatus exitstatus) {
    SYSLOG(DEBUG) << "ExitCode: " << exitcode;
    SYSLOG(INFO) << "ExitStatus: " << exitstatus;
}

/**
 * @brief Rdp::processError
 * @param err
 */
void Rdp::processError(QProcess::ProcessError err)
{
    switch(err)
    {
    case QProcess::FailedToStart:
        QMessageBox::information(0,"FailedToStart","FailedToStart");
        SYSLOG(ERROR) << "Failed to start";
        break;
    case QProcess::Crashed:
        QMessageBox::information(0,"Crashed","Crashed");
        SYSLOG(ERROR) << "Crashed";
        break;
    case QProcess::Timedout:
        QMessageBox::information(0,"Timedout","Timedout");
        SYSLOG(ERROR) << "Timedout";
        break;
    case QProcess::WriteError:
        QMessageBox::information(0,"WriteError","WriteError");
        SYSLOG(ERROR) << "WriteError";
        break;
    case QProcess::ReadError:
        QMessageBox::information(0,"ReadError","ReadError");
        SYSLOG(ERROR) << "ReadError";
        break;
    case QProcess::UnknownError:
        QMessageBox::information(0,"UnknownError","UnknownError");
        SYSLOG(ERROR) << "UnknownError";
        break;
    default:
        QMessageBox::information(0,"default","default");
        break;
    }
}
