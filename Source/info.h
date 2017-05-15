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

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
class QLabel;
class QPlainTextEdit;
class QLineEdit;

QT_END_NAMESPACE

class Info : public QWidget
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

public slots:
	void changePic();

public:
	Info(QWidget *parent = 0);
	Info(Person src);
	~Info();
	Person export_data();
};

#endif // INFO_H
