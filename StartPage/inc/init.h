#ifndef INIT_H
#define INIT_H
#include <QString>
#include <QPair>

class Init {
	
	public:
		Init();
		Init(QString empty);

		// delete the copy contructors, because they are not needed and
		// otherwise there will be problems with the copying of the ui* pointer
		//Init(const Init&) = delete;
		//Init* operator=(const Init&) = delete;
		Init(const Init& x); //copy-constructor

        //getter script --> returns path to script
        QString get_script_ip();
		QString get_script_netmask();
		QString get_script_gateway();

        //getter ConfigPage --> reads variables from configpage file
		QString get_client_logo();
		QString get_network_type();
		QString get_citrix_rdp_type();
		QString get_citrix_store();
		QString get_citrix_url();
		QString get_rdp_server();
		QString get_rdp_domain();
        QString get_language();

	private:
        // vars script paths
		QString script_ip;
		QString script_netmask;
		QString script_gateway;

        // vars from ConfigPage
		QString client_logo;
		QString network_type;
		QString citrix_rdp_type;
		QString citrix_store;
		QString citrix_url;
		QString rdp_server;
		QString rdp_domain;
        QString language;

};


#endif // INIT_H
