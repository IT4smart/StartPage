#include "storebrowse.h"
#include "startpage.h"

/*
 * constructor Storebrowse
 */
Storebrowse::Storebrowse(QString netscaler_url, QString store_url, QString username, QString password) {
    // set netscaler and store vars
    this->netscaler_url = netscaler_url;
    this->store_url = store_url;

    // Set login variables
    this->username = username.toStdString();
    this->password = password.toStdString();

    // Name of the shared memory segment
    shared_memory_key = 1234;

    shared_memory_init();
    shared_memory_struct_init();

    loginProcess = NULL;
}

Storebrowse::~Storebrowse() {
    shmctl(shared_memory_ID, IPC_RMID, NULL);
}

void Storebrowse::shared_memory_init(void) {

    // Create the shared memory segment
    shared_memory_ID = shmget(shared_memory_key, sizeof(sharedStruct), IPC_CREAT | 0666);

    // Now we attach the segment to our data space.
    shared_memory = shmat(shared_memory_ID, NULL, 0);

    // Set sharedStruct to shared memory
    shared_memory_struct = (sharedStruct*) shared_memory;

}

void Storebrowse::shared_memory_struct_init(void) {
    shared_memory_struct->terminated = false;
    shared_memory_struct->login_success = false;
    shared_memory_struct->n_login = 0;
    strcpy(shared_memory_struct->username, this->username.c_str());
    strcpy(shared_memory_struct->password, this->password.c_str());
}



/*
 * @brief Citrix::getActualStore
 * @return
 */
QString Storebrowse::getActualStore() {
    // run system command
    QString command = PRG_STOREBROWSE + " -l '" + this->store_url + "'";
    QPair<QString,QString> ret_pair = StartPage::exec_cmd_process(command);

    return ret_pair.first; // return only storeaddress
}

/*
 * addStore --> login window might appear
 * @brief Storebrowse::addStore
 */
void Storebrowse::addStore() {
//    qDebug() << "addStore";
    // run system command
    QString command = PRG_STOREBROWSE + " -a '" + this->netscaler_url + "'";
    QPair<QString,QString> ret_pair = StartPage::exec_cmd_process(command);
//    qDebug() << "return:\n" << ret_pair.first << "\nerror:\n" << ret_pair.second;
}

/*
 * get desktops from store
 */
QMap<QString,QString> Storebrowse::getDesktops() {
    QMap<QString, QString> ret_map; // initiate return map

    // run system command
    QString command = PRG_STOREBROWSE+" -E '"+this->store_url+"'";
    QPair<QString,QString> pair = StartPage::exec_cmd_process(command); // returns result and error as QPair
    QString result = pair.first;
    QString error = pair.second;

    // error handling
    if (result=="") { // there is no result
        // determine error
        QString err_type;
        if (error.contains("ERROR_HTTP")) { // no web connection
            err_type = "HTTP ERROR!";
        } else if (error.contains("AUTH_SERVER")) { // authorization error
            err_type = "AUTH_SERVER ERROR!";
        } else if (error.contains("OUT_OF_LICENSES")) {
            err_type = "OUT_OF_LICENSES ERROR!";
        } else {
            err_type = "USER/PW ERROR!";
        }

        ret_map.insert("ERROR", err_type);
        return ret_map; // return map

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
QPair<QString,QString> Storebrowse::startDesktop(QString desktop_link) {
    // run system command
    QString command = PRG_STOREBROWSE + " -L '" + desktop_link + "' '" + this->store_url + "'";
    QPair<QString,QString> ret_pair = StartPage::exec_cmd_process(command);

    // return QPair
    return ret_pair;
}

/*
 * delete citrix login information
 */
QPair<QString,QString> Storebrowse::deleteCitrixAuthentication() {
//qDebug() << "deleteCitrixAuthentication ...";
    // run system command
    QString command = PRG_KILLALL+" "+PROC_AUTHMANAGERDAEMON+" "+PROC_SERVICERECORD+" "+PROC_STOREBROWSE;
    QPair<QString,QString> ret_pair = StartPage::exec_cmd_process(command);

    // return QPair
    return ret_pair;
}



