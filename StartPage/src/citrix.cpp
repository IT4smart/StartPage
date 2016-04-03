#include <QProcess>
#include "../inc/citrix.h"
#include "../../../libs/tools/inc/exec_cmd.h"
#include <QDebug>
#include <QPair>

/*
 * constructor
 *
 * parameter:
 * link_netscaler = external link of netscaler gateway, e.g. https://extern.ass-hn.de
 * link_store = internal link of chosen store, e.g. https://ddcxd1.ass-hn.de/citrix/xdstore/discovery
 */
Citrix::Citrix(QString _link_netscaler, QString _link_store):
    link_netscaler(_link_netscaler), link_store(_link_store)
{

}

/*
 * get desktops from store
 */
QMap<QString,QString> Citrix::getDesktops() {
    QMap<QString, QString> ret_map; // initiate return map

    // run system command
    QString command = PRG_STOREBROWSE+" -E '"+link_store+"'";
    QPair<QString,QString> pair = exec_cmd_process(command); // returns result and error as QPair
    QString result = pair.first;
    QString error = pair.second;

    // error handling
    if (result=="") { // there is no result --> empty
        // do something later
        if (error.contains("ERROR_HTTP")) { // no web connection
            qDebug() << "HTTP ERROR!";
        } else if (error.contains("AUTH_SERVER")) { // authorization error
            qDebug() << "AUTH_SERVER ERROR!";
        } else if (error.contains("OUT_OF_LICENSES")) {
            qDebug() << "OUT_OF_LICENSES ERROR!";
        } else {
            qDebug() << "error:" << error;
        }
        return ret_map; // return empty map

    } else { // there is a result --> compute it
        // split str
        QString sbuf = QString(pair.first.data()); // get buffer result
        sbuf.remove("'"); // remove '-char

        // cut in rows
        QStringList rows = sbuf.split("\n", QString::SkipEmptyParts);
        for (int i=0;i<rows.size();i++) {
            // cut row in colums
            QStringList colums = rows.at(i).split("\t", QString::SkipEmptyParts);
            ret_map.insert(colums.at(1), colums.at(0));
        }

        return ret_map; // return full map
    }

}

/*
 * start desktop with desktop link --> login window might appear
 *
 * parameter:
 * desktopLink
 *
 * return: QPair<QString,QString> (= <buffer_result,buffer_error)
 */
QPair<QString,QString> Citrix::startDesktop(QString desktop_link) {
    // run system command
    QString command = PRG_STOREBROWSE + " -L '" + desktop_link + "' '" + link_store + "'";
    QPair<QString,QString> ret_pair = exec_cmd_process(command);

    // return QPair
    return ret_pair;
}

/*
 * delete citrix login information
 */
QPair<QString,QString> Citrix::deleteCitrixAuthentication() {
qDebug() << "deleteCitrixAuthentication ...";
    // run system command
    QString command = PRG_KILLALL+" "+PROC_AUTHMANAGERDAEMON+" "+PROC_SERVICERECORD;
    QPair<QString,QString> ret_pair = exec_cmd_process(command);

qDebug() << "deleteCitrixAuthentication: result:\n" << ret_pair.first << "\nerror:" << ret_pair.second;

    // return QPair    
    return ret_pair;
}


/**
 * @brief Citrix::getActualStore
 * @return
 */
QString Citrix::getActualStore() {
    // run system command
    QString command = PRG_STOREBROWSE + " -l '" + link_netscaler + "'";
    QPair<QString,QString> ret_pair = exec_cmd_process(command);

    return ret_pair.first; // return only storeaddress
}


/** addStore --> login window might appear
 * @brief Citrix::addStore
 */
void Citrix::addStore() {
    qDebug() << "addStore";
    // run system command
    QString command = PRG_STOREBROWSE + " -a '" + link_netscaler + "'";
    QPair<QString,QString> ret_pair = exec_cmd_process(command);
    qDebug() << "return:\n" << ret_pair.first << "\nerror:\n" << ret_pair.second;
}


