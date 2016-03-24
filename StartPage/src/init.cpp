//init.cpp

#include "../inc/init.h"
#include <QProcess>
#include <iostream>
#include <memory>
#include "../../../libs/tools/inc/paths.h"
#include "../../../libs/tools/inc/IniFile.h"
#include "../../../libs/tools/inc/custom_exceptions.h"
#include "../../../libs/tools/inc/exec_cmd.h"

#include "../../../libs/tools/inc/maps.h" //for printing mapmaps



/**
 * empty constructor so no exceptions will appear in the initializerlist of mainwindow
 */
Init::Init(QString empty) :
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
	(void) empty;
}
/**
 * Copy-Constructor
 * use with: init = Init();
 */
Init::Init(const Init& x) : 
	script_ip(x.script_ip),
	script_netmask(x.script_netmask),
	script_gateway(x.script_gateway),
 	client_logo(x.client_logo), 
 	network_type(x.network_type), 
	citrix_rdp_type(x.citrix_rdp_type), 
	citrix_store(x.citrix_store), 
	citrix_url(x.citrix_url), 
	rdp_server(x.rdp_server), 
	rdp_domain(x.rdp_domain) 
{}

/**
 * Constructor
 * read the setting.ini (path in paths.h)
 * get the path + name of the scripts, that can be executed to get ip, etc
 * executes the Configpage under the given path in setting.ini and gets the information 
 * of logos, networktype, etc
 * save all important variables in the member variables
 * @throw developer_error if setting.ini can't be read
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

	//reads out the setting.ini under the given path saved in paths.h
	//this line may throw developer_error
	std::unique_ptr<IniFile> setting(new IniFile(SETTING_PATH, SETTING_FILE, SETTING_ENDING));
	//read 
	this->script_ip			= "./" + setting.get()->get_Map_Value("script", "get_ip");
	this->script_netmask		= "./" + setting.get()->get_Map_Value("script", "get_netmask");
	this->script_gateway		= "./" + setting.get()->get_Map_Value("script", "get_gateway");

	//read out the part from ConfigPage setting.ini
	QString configPath		= setting.get()->get_Map_Value("ConfigPage", "path") + "/";
	QString configExec		= setting.get()->get_Map_Value("ConfigPage", "exec");
	QString configPage 		= "cd " + configPath + " && " + "./" + configExec + " "; 
	QString config_client_logo	= setting.get()->get_Map_Value("ConfigPage", "client_logo");
	QString config_network_type	= setting.get()->get_Map_Value("ConfigPage", "network_type");
	QString config_citrix_rdp_type	= setting.get()->get_Map_Value("ConfigPage", "citrix_rdp_type");
	QString config_citrix_store	= setting.get()->get_Map_Value("ConfigPage", "citrix_store");
	QString config_citrix_url	= setting.get()->get_Map_Value("ConfigPage", "citrix_url");
	QString config_rdp_server	= setting.get()->get_Map_Value("ConfigPage", "rdp_server");
	QString config_rdp_domain	= setting.get()->get_Map_Value("ConfigPage", "rdp_domain");
    QString config_language	= setting.get()->get_Map_Value("ConfigPage", "language");


	//set the internal variables
	this->client_logo 	= 	configPath + exec_cmd_process_re_QString(configPage + config_client_logo);
	this->network_type 	= 	exec_cmd_process_re_QString(configPage + config_network_type);
	this->citrix_rdp_type	= 	exec_cmd_process_re_QString(configPage + config_citrix_rdp_type);
	this->citrix_store	= 	exec_cmd_process_re_QString(configPage + config_citrix_store);
	this->citrix_url	= 	exec_cmd_process_re_QString(configPage + config_citrix_url);
	this->rdp_server	= 	exec_cmd_process_re_QString(configPage + config_rdp_server);
	this->rdp_domain	= 	exec_cmd_process_re_QString(configPage + config_rdp_domain);
    this->language      = 	exec_cmd_process_re_QString(configPage + config_language);

	//test:
	///*
	   print_MapMap_to_stdout(setting.get()->get_Map());
	   std::cout << script_ip.toStdString() << std::endl;
	   std::cout << "network_type command: '" << config_network_type << "'" << std::endl;
	   std::cout << "network_type: '" << network_type.toStdString() << "'" << std::endl;
	   std::cout << "citrix_rdp_type: '" << citrix_rdp_type.toStdString() << "'" << std::endl;
	   std::cout << configPage + config_citrix_rdp_type << std::endl;
	   std::cout << "client_logo: '" << client_logo.toStdString() << "'" << std::endl;
	   std::cout << "citrix_store: '" << citrix_store.toStdString() << "'" << std::endl;
	   std::cout << "citrix_url: '" << citrix_url.toStdString() << "'" << std::endl;
       std::cout << "language: '" << language.toStdString() << "'" << std::endl;

    //*/
}




/**********************************************************************
 **********************************************************************
 *				getter script
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
 * @return client_logo path + name of the logo
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

/**
 * getter
 * @return language
 */
QString Init::get_language() {
    return this->language;
}
