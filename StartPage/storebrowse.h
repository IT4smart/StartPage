#ifndef STOREBROWSE_H
#define STOREBROWSE_H

#include <QString>
#include <QDebug>
#include <QProcess>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>

const QString PRG_STOREBROWSE = "/opt/Citrix/ICAClient/util/storebrowse";
const QString PRG_KILLALL = "/usr/bin/killall";
const QString PROC_AUTHMANAGERDAEMON = "AuthManagerDaemon";
const QString PROC_SERVICERECORD = "ServiceRecord";

struct sharedStruct {
    bool terminated;
    bool login_success;
    int n_login;
    char username[128];
    char password[128];
};

class Storebrowse {
    public:

//        bool try_login(void); // login procedure

        // methods
        Storebrowse(QString netscaler_url, QString store_url, QString username, QString password);
        ~Storebrowse();
        void addStore(); // add store
        QString getActualStore(); // get actual stores
        QMap<QString,QString> getDesktops(); // get desktops from store, return: QMap with <key,value>
        QPair<QString,QString> startDesktop(QString link_desktop); // start desktop with desktop link
        QPair<QString,QString> deleteCitrixAuthentication(); // delete citrix login information

        // vars

    private:
        // methods
        void shared_memory_init(void);
        void shared_memory_struct_init(void);

        // vars
        QString netscaler_url; // constructor stores here the netscaler url
        QString store_url; // constructor stores here the store url
        std::string username;
        std::string password;
        QProcess *loginProcess;

        // Shared memory:
        key_t shared_memory_key;
        int shared_memory_ID;
        void *shared_memory;
        sharedStruct *shared_memory_struct;

};

#endif // STOREBROWSE_H
