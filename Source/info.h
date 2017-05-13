#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QPixmap>
#include <QImage>

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

public slots:
	void changePic();

public:
	Info(QWidget *parent = 0);
	~Info();
};

#endif // INFO_H
