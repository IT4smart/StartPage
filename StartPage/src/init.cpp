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
Init::Init() :
	script_ip(),
	script_netmask(),
	script_gateway(),
 	client_logo(), 
 	network_type(), 
	citrix_rdp_type(), 
	citrix_store(), 
	citrix_url(), 
	rdp_server(), 
	rdp_domain() 
{
	
	//std::cout << "Init Constructor\n";
	std::unique_ptr<Setting> setting(new Setting);
	try {
		setting.get()->loadSettings();
	} catch(const developer_error& e) {
		//TODO
		std::cout << -1 << "Load Setting in Init-Konstruktor nicht geklappt" << std::endl;
	}
	auto& setting_map 		= setting.get()->getSetting();
	//script
	this->script_ip			= "./" + setting_map.value("script")	.value("get_ip");
	this->script_netmask		= "./" + setting_map.value("script")	.value("get_netmask");
	this->script_gateway		= "./" + setting_map.value("script")	.value("get_gateway");

	//ConfigPage
	QString configPath		= setting_map.value("ConfigPage")	.value("path") + "/";
	QString configExec		= setting_map.value("ConfigPage")	.value("exec");
	QString configPage 		= "cd " + configPath + " && " + "./" + configExec + " "; 
	QString config_client_logo	= setting_map.value("ConfigPage")	.value("client_logo");
	QString config_network_type	= setting_map.value("ConfigPage")	.value("network_type");
	QString config_citrix_rdp_type	= setting_map.value("ConfigPage")	.value("citrix_rdp_type");
	QString config_citrix_store	= setting_map.value("ConfigPage")	.value("citrix_store");
	QString config_citrix_url	= setting_map.value("ConfigPage")	.value("citrix_url");
	QString config_rdp_server	= setting_map.value("ConfigPage")	.value("rdp_server");
	QString config_rdp_domain	= setting_map.value("ConfigPage")	.value("rdp_domain");

//TODO execute "./" + script_map

	//test:
	//std::cout << script_ip.toStdString() << std::endl;
	//std::cout << "network_type command: '" << config_network_type << "'" << std::endl;

	
	this->client_logo 	= 	configPath + exec_cmd_process_reStr(configPage + config_client_logo);
	this->network_type 	= 	exec_cmd_process_reStr(configPage + config_network_type);
	this->citrix_rdp_type	= 	exec_cmd_process_reStr(configPage + config_citrix_rdp_type);
	this->citrix_store	= 	exec_cmd_process_reStr(configPage + config_citrix_store);
	this->citrix_url	= 	exec_cmd_process_reStr(configPage + config_citrix_url);
	this->rdp_server	= 	exec_cmd_process_reStr(configPage + config_rdp_server);
	this->rdp_domain	= 	exec_cmd_process_reStr(configPage + config_rdp_domain);
	//std::cout << "network_type: '" << network_type.toStdString() << "'" << std::endl;
	//std::cout << "citrix_rdp_type: '" << citrix_rdp_type.toStdString() << "'" << std::endl;
	//std::cout << configPage + config_citrix_rdp_type << std::endl;
	std::cout << "client_logo: '" << client_logo.toStdString() << "'" << std::endl;
	std::cout << "citrix_store: '" << citrix_store.toStdString() << "'" << std::endl;
	std::cout << "citrix_url: '" << citrix_url.toStdString() << "'" << std::endl;

}





/*
 * @param cmd e.g. ./script/print_ip.sh, or "cd ../../configurationpage/ConfigPage && ./Configpage network_type"
 * @return first line of output
 */
QString exec_cmd_process_reStr(QString cmd) {

	QStringList lines = exec_cmd_process(cmd);
	if (!lines.isEmpty())
		return lines[0];
	else 
		return "";
}


/* TODO
 * @param cmd e.g. ./script/print_ip.sh, or "cd ../../configurationpage/ConfigPage && ./Configpage network_type"
 * @return output of cmd as line-list
 */
QStringList exec_cmd_process(QString cmd) {
	QProcess *process;
	process = new QProcess(); // start process

	process->start("sh");
	process->write(cmd.toLatin1());
	process->closeWriteChannel();

	QByteArray buffer;
	QByteArray buffer_error;
	while(process->waitForFinished()) {
		buffer.append(process->readAllStandardOutput());
		buffer_error.append(process->readAllStandardError());
	}
	process->close();


	// split str
	QString sbuf = buffer.data();
	//sbuf.remove("'"); // remove '-characters
	QStringList lines = sbuf.split("\n", QString::SkipEmptyParts);
	if (!lines.isEmpty()) {
		/*for(int i = 0; i < lines.size(); i++) {
			std::cout << "Test: " << lines[i] << std::endl;
		}*/
		//std::cout << "Test: " << sbuf << std::endl;
		return lines;
	} else {
		//TODO emtpy return -> handle
	}
	return lines;
	//TODO handle buffer_error
}
/**********************************************************************
 **********************************************************************
 *				getter ConfigPage
 **********************************************************************
 **********************************************************************/
/**
 * getter
 * @return script_ip cmd to execute
 */
QString Init::get_script_ip() {
	return this->script_ip;
}

/**
 * getter
 * @return script_netmask cmd to execute
 */
QString Init::get_script_netmask() {
	return this->script_netmask;
}

/**
 * getter
 * @return script_gateway cmd to execute
 */
QString Init::get_script_gateway() {
	return this->script_gateway;
}

/**********************************************************************
 **********************************************************************
 *				getter ConfigPage
 **********************************************************************
 **********************************************************************/

/**
 * getter
 * @return client_logo path
 */
QString Init::get_client_logo() {
	return this->client_logo;
}

/**
 * getter
 * @return network_type
 */
QString Init::get_network_type() {
	return this->network_type;
}

/**
 * getter
 * @return citrix_rdp_type
 */
QString Init::get_citrix_rdp_type() {
	return this->citrix_rdp_type;
}

/**
 * getter
 * @return citrix_store
 */
QString Init::get_citrix_store() {
	return this->citrix_store;
}

/**
 * getter
 * @return citrix_url
 */
QString Init::get_citrix_url() {
	return this->citrix_url;
}

/**
 * getter
 * @return rdp_server
 */
QString Init::get_rdp_server() {
	return this->rdp_server;
}

/**
 * getter
 * @return rdp_domain
 */
QString Init::get_rdp_domain() {
	return this->rdp_domain;
}

