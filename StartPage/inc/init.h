#ifndef INIT_H
#define INIT_H
#include <QString>

class Init {
	
	public:
		Init();

		// delete the copy contructors, because they are not needed and
		// otherwise there will be problems with the copying of the ui* pointer
		Init(const Init&) = delete;
		Init* operator=(const Init&) = delete;

	private:

	QString exec_script(QString script_full_path);
	QString exec_script(QString script_full_path, QStringList arguments);
	QString exec_script(QString script_full_path, QString argument);
};


#endif // INIT_H
