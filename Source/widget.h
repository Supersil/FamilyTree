#ifndef WIDGET_H
#define WIDGET_H

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

class Widget : public QWidget
{
	Q_OBJECT
private:

	QSplitter * vertical;
	QLabel *portraitLabel;
	QLineEdit *fioEdit;
	QLineEdit *birthEdit;
	QPlainTextEdit *infoText;

public:
	Widget(QWidget *parent = 0);
	~Widget();
};

#endif // WIDGET_H
