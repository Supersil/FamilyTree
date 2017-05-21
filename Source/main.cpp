#include "info.h"
#include <QApplication>
#include "person.h"
#include "mainwindow.h"
#include "info.h"
#include <QObject>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow m;
	m.show();

	return a.exec();
}
