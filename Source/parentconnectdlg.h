#ifndef PARENTCONNECTDLG_H
#define PARENTCONNECTDLG_H

#include <QObject>
#include <QDialog>
#include <QComboBox>
#include "person.h"
#include <QPushButton>
#include <QGridLayout>

class ParentConnectDlg: public QDialog
{
	Q_OBJECT

private:
	QComboBox * parents;
	QList<Person *> personList;
public:
	ParentConnectDlg(QList<Person *> list);

private slots:
	void save_and_exit();

signals:
	void export_person(Person * profile);
};

#endif // PARENTCONNECTDLG_H
