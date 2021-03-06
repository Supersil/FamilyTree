#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QPixmap>
#include <QImage>
#include "person.h"
#include <QDialog>
#include <QCheckBox>
#include <QComboBox>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
class QLabel;
class QPlainTextEdit;
class QLineEdit;

QT_END_NAMESPACE

class Info : public QDialog
{
	Q_OBJECT
private:

	QLabel *portraitLabel;
	QLineEdit *fioEdit;
	QLineEdit *birthEdit;
	QPlainTextEdit *infoText;
	QLineEdit *birthPlace;
	QString photoPath;
	QLineEdit * deathEdit;
	QCheckBox * aliveCheck;
	QComboBox * sexBox;

public slots:
	void changePic();
	void saveAndClose();

public:
//	Info(QWidget *parent = 0);
	Info(Person *src = 0, QWidget *parent = 0);
	~Info();
	void export_data();

signals:
	void export_person(Person * profile);


};

#endif // INFO_H
