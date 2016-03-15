#ifndef UNITTEST_H
#define UNITTEST_H


//included dependencies
#include <QTest>

class Test : public QObject {
	Q_OBJECT

	//all test-functions as private slots
	private slots:
		void example();
};

#endif // UNITTEST_H


