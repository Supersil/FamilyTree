#include "info.h"
#include <QApplication>
#include "person.h"
#include "mainwindow.h"
#include "info.h"
#include <QObject>
#include "parentconnectdlg.h"
#include <QImage>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


   MainWindow m;
   m.show();


//	QList<Person *> list;

//	Person *  me = new Person(QDate(1992,6,12),"Силков Александр Андреевич","Создатель программы","Москва",":/me.jpg",MALE);
//	Person *  dad = new Person(QDate(1970,10,24),"Силков Андрей Николаевич","Папа","Москва",":/dad.jpg",MALE);
//	Person *  mom = new Person(QDate(1971,7,29),"Силкова Светлана Сергеевна","Мама","Солнцево",":/mom.jpg",FEMALE);
//	Person *  granm = new Person(QDate(1950,3,5),"Бабенко Любовь Тихоновна","Бабушка","Льгов",":/grandm.jpg",FEMALE);
//	Person *  grand = new Person(QDate(1900,1,1),QDate(1992,6,20),false,"Бабенко Сергей","Дедушка","Льгов",":/no_photo.jpg",MALE);

//	list.append(me);
//	list.append(dad);
//	list.append(mom);
//	list.append(granm);
//	list.append(grand);

//   QImage img(":/me.jpg");
//   qint32 len = img.byteCount();
//   uchar * data;// = new char[len];
//   int f = img.format();
//   data = img.bits();
//   QImage img2(data,img.width(),img.height(),(QImage::Format)f);
//   img2.save("111.jpg");

//	ParentConnectDlg dlg(list);
//	dlg.show();

	return a.exec();
}
