#include "widget.h"
#include <QGridLayout>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	//left side
	QLabel * nameLabel = new QLabel(tr("ФИО: "));
	fioEdit = new QLineEdit(tr("Иванов Иван Иванович"));
	fioEdit->setFixedWidth(300);
	QLabel * birthLabel = new QLabel(tr("Дата Рождения: "));
	birthEdit = new QLineEdit(tr("01.01.1900"));
	QLabel * infoLabel = new QLabel(tr("Информация:"));
	infoText = new QPlainTextEdit(tr("Родился в Москве, женился, родил."));
	QGridLayout * mainLayout = new QGridLayout;

	mainLayout->addWidget(nameLabel,0,0,Qt::AlignLeft);
	mainLayout->addWidget(fioEdit,0,1,Qt::AlignRight);
	mainLayout->addWidget(birthLabel,1,0,Qt::AlignLeft);
	mainLayout->addWidget(birthEdit,1,1,Qt::AlignRight);
	mainLayout->addWidget(infoLabel,2,0,1,2,Qt::AlignCenter);
	mainLayout->addWidget(infoText,3,0,3,2);




	portraitLabel = new QLabel;
	QImage img(tr("1.png"));
	portraitLabel->setPixmap(QPixmap::fromImage(img));
	portraitLabel->adjustSize();

	vertical = new QSplitter;
//	vertical->setOrientation(Qt::vertical);
	QWidget * wid = new QWidget;
	wid->setLayout(mainLayout);
	vertical->addWidget(wid);
	vertical->addWidget(portraitLabel);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(vertical);
	setLayout(layout);
//	setLayout(mainLayout);
//	setWindowTitle(tr("Profile"));

}

Widget::~Widget()
{
	delete fioEdit;
	delete birthEdit;
	delete infoText;
}
