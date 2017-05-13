#include "info.h"
#include <QApplication>
#include "person.h"
#include "mainwindow.h"
#include "info.h"

// test

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	Info w;
	w.show();


//	MainWindow m;
//	m.show();

	return a.exec();
}
