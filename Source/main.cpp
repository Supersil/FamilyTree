#include "info.h"
#include <QApplication>
#include "person.h"
#include "mainwindow.h"
#include "info.h"
#include <QObject>
// test

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);

	Person me(QDate(1992,06,12),QObject::tr("Силков Александр Андреевич"),
				 QObject::tr("Создатель программы"),QObject::tr("Москва"),
				 QObject::tr(":/me.jpg"));

	Info w(me);
	w.show();


//	MainWindow m;
//	m.show();

	return a.exec();
}
