//init.cpp

#include "../inc/init.h"
#include <QProcess>
#include <iostream>
#include <memory>
#include "../../../libs/tools/inc/setting.h"
#include "../../../libs/tools/inc/custom_exceptions.h"

/**
 * Constructor
 */
Init::Init() {
	
	std::cout << "Init Constructor\n";
	std::unique_ptr<Setting> setting(new Setting);
	try {
		setting.get()->loadSettings();
	} catch(const developer_error& e) {
		//TODO
		std::cout << -1 << "Load Setting in Init-Konstruktor nicht geklappt" << std::endl;
	}
	auto& setting_map 	= setting.get()->getSetting();
	QString script_ip	= setting_map.value("script")	.value("get_ip");
	QString script_netmask	= setting_map.value("script")	.value("get_netmask");
	QString script_gateway	= setting_map.value("script")	.value("get_gateway");

	//ConfigPage
	QString configPath	= setting_map.value("ConfigPage")	.value("path");
	QString configExec	= setting_map.value("ConfigPage")	.value("exec");
	QString configPage	= configPath + "/" + configExec;
	QString config_network_type	= setting_map.value("ConfigPage")	.value("network_type");



	//test:
	std::cout << script_ip.toStdString() << std::endl;

	QString ip = exec_script(script_ip);

	std::cout << ip.toStdString() << std::endl;


	QString network_type = exec_script(configPage, config_network_type);
	std::cout << "network_type command: '" << config_network_type << "'" << std::endl;
	std::cout << "network_type: '" << network_type.toStdString() << "'" << std::endl;

	//TODO qtprocess mit sh starten und dann write machen, danach kann man in der bash in den richtigen ordner wechseln
	//und dann im richtigen Ordner ConfigPage ausführen
	

	QProcess *procCitrix;
	procCitrix = new QProcess(); // start process for citrix

	procCitrix->start("sh");
	//procCitrix->write("/opt/Citrix/ICAClient/util/storebrowse -E 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'");
	QString cmd = "cd " + configPath + " && " + "./" + configExec + " " + config_network_type; 
	procCitrix->write(cmd.toLatin1());
	procCitrix->closeWriteChannel();

	QByteArray buffer;
	QByteArray buffer_error;
	while(procCitrix->waitForFinished()) {
		buffer.append(procCitrix->readAllStandardOutput());
		buffer_error.append(procCitrix->readAllStandardError());
	}
	procCitrix->close();

	//qDebug(buffer.data());
	//ui->lblDebugLine->setText(QString(buffer_error).toLatin1());

	// split str
	QString sbuf = buffer.data();
	//sbuf.remove("'"); // remove '-zeichen
	QStringList zeilen = sbuf.split("\n", QString::SkipEmptyParts);
	if (!zeilen.isEmpty()) {
		for(int i = 0; i < zeilen.size(); i++) {
			std::cout << "Test: " << zeilen[i] << std::endl;
		}
		//std::cout << "Test: " << sbuf << std::endl;
	}




}



/**
 * @param script_full_path e.g. ./script/print_ip.sh
 * @return output of script
 */
QString Init::exec_script(QString script_full_path) {
	return exec_script(script_full_path, QStringList());
}

/**
 * @param script_full_path e.g. ./script/print_ip.sh
 * @return output of script
 */
QString Init::exec_script(QString script_full_path, QString argument) {
	return exec_script(script_full_path, QStringList(argument));
}


/**
 * @param script_full_path e.g. ./script/print_ip.sh
 * @param arguments a list of arguments passed to
 * @return output of script
 */
QString Init::exec_script(QString script_full_path, QStringList arguments) {

	QProcess *procSystem; // process for system commands
	procSystem = new QProcess();
	procSystem->start(script_full_path, arguments);
	procSystem->waitForFinished();
	QString output = procSystem->readAllStandardOutput();
	return output;
}


