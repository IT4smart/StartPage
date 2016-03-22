#ifndef CITRIX_H
#define CITRIX_H

#include <QString>
#include <QMap>
#include <QPair>
#include <QString>

const QString PRG_STOREBROWSE = "/opt/Citrix/ICAClient/util/storebrowse";
const QString PRG_KILLALL = "/usr/bin/killall";
const QString PROC_AUTHMANAGERDAEMON = "AuthManagerDaemon";
const QString PROC_SERVICERECORD = "ServiceRecord";

/*
 * class manages communication with citrix server
 */
class Citrix {

    public:
        /*
         * constructor
         *
         * parameter:
         * link_netscaler = external link of netscaler gateway, e.g. https://extern.ass-hn.de
         * link_store = internal link of chosen store, e.g. https://ddcxd1.ass-hn.de/citrix/xdstore/discovery
         */
        Citrix(QString link_netscaler, QString link_store); // constructor

        QMap<QString,QString> getDesktops(); // get desktops from store, return: QMap with <key,value>
        QPair<QByteArray,QByteArray> startDesktop(QString link_desktop); // start desktop with desktop link
        QPair<QByteArray,QByteArray> deleteCitrixAuthentication(); // delete citrix login information

   private:
        QString link_netscaler; // external link of Netscaler
        QString link_store; // internal link of chosen store

//        QStringList getStores(); // get list of stores
//        void addStore(); // add store --> login window will appear

};

#endif // CITRIX_H
