#include <QProcess>
#include "../inc/citrix.h"
#include "../../../libs/tools/inc/exec_cmd.h"

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
    QPair<QByteArray,QByteArray> pair = exec_cmd_process(command);

    // split str
    QString sbuf = pair.first.data(); // get buffer result
    sbuf.remove("'"); // remove '-char

    // cut in rows
    QStringList rows = sbuf.split("\n", QString::SkipEmptyParts);
    for (int i=0;i<rows.size();i++) {
        // cut row in colums
        QStringList colums = rows.at(i).split("\t", QString::SkipEmptyParts);
        ret_map.insert(colums.at(1), colums.at(0));
    }

    return ret_map;
}

/*
 * start desktop with desktop link --> login window might appear
 *
 * parameter:
 * desktopLink
 *
 * return: QPair<QByteArray,QByteArray> (= <buffer_result,buffer_error)
 */
QPair<QByteArray,QByteArray> Citrix::startDesktop(QString desktop_link) {
    // run system command
    QString command = PRG_STOREBROWSE + " -L '" + desktop_link + "' '" + link_store + "'";
    QPair<QByteArray,QByteArray> ret_pair = exec_cmd_process(command);

    // return QPair
    return ret_pair;
}

/*
 * delete citrix login information
 */
QPair<QByteArray,QByteArray> Citrix::deleteCitrixAuthentication() {
    // run system command
    QString command = PRG_KILLALL+" "+PROC_AUTHMANAGERDAEMON+" "+PROC_SERVICERECORD;
    QPair<QByteArray,QByteArray> ret_pair = exec_cmd_process(command);

    // return QPair
    return ret_pair;
}

/*
 * get list of stores
 */
/*QStringList Citrix::getStores() {
}*/

/*
 * add store --> login window might appear
 */
/*void Citrix::addStore() {
}*/


