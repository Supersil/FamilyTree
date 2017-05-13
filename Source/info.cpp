#include "info.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>


Info::Info(QWidget *parent)
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

	QLabel * placeLabel = new QLabel(tr("Место Рождения: "));
	birthPlace = new QLineEdit("город Москва");

	infoText->setMinimumHeight(300);

	mainLayout->addWidget(nameLabel,0,0,Qt::AlignLeft);
	mainLayout->addWidget(fioEdit,0,1,Qt::AlignRight);
	mainLayout->addWidget(birthLabel,1,0,Qt::AlignLeft);
	mainLayout->addWidget(birthEdit,1,1);
	mainLayout->addWidget(placeLabel,2,0,Qt::AlignLeft);
	mainLayout->addWidget(birthPlace,2,1);
	mainLayout->addWidget(infoLabel,3,0,1,2,Qt::AlignCenter);
	mainLayout->addWidget(infoText,4,0,3,2);




	portraitLabel = new QLabel;
	QImage img(tr(":/no_photo.jpg"));
	portraitLabel->setPixmap(QPixmap::fromImage(img.scaled(300,400)));
	portraitLabel->adjustSize();


	mainLayout->addWidget(portraitLabel,0,2,6,1);

	QPushButton * changePhoto = new QPushButton(tr("Изменить фотографию"));
	mainLayout->addWidget(changePhoto,6,2);

	connect(changePhoto,SIGNAL(pressed()),this,SLOT(changePic()));

	setLayout(mainLayout);
	setWindowTitle(tr("Профиль"));

}

Info::~Info()
{
	delete fioEdit;
	delete birthEdit;
	delete infoText;
	delete portraitLabel;
	delete birthPlace;
}

void Info::changePic()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		 tr("Open Image"),"C:/", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
	QImage newpic(fileName);
	portraitLabel->setPixmap(QPixmap::fromImage(newpic.scaled(300,400)));
	portraitLabel->adjustSize();
}
