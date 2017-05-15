#include "info.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QCheckBox>

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


	QCheckBox * check = new QCheckBox(tr("Живой"));
	check->setChecked(1);
	QLabel * deadLabel = new QLabel(tr("Дата смерти: "));
	deathEdit = new QLineEdit(tr("01.01.1900"));


	mainLayout->addWidget(nameLabel,0,0,Qt::AlignLeft);
	mainLayout->addWidget(fioEdit,0,1,1,2,Qt::AlignRight);
	mainLayout->addWidget(birthLabel,1,0,Qt::AlignLeft);
	mainLayout->addWidget(birthEdit,1,1,1,2);
	mainLayout->addWidget(placeLabel,2,0,Qt::AlignLeft);
	mainLayout->addWidget(birthPlace,2,1,1,2);

	mainLayout->addWidget(check,3,0);
	mainLayout->addWidget(deadLabel,3,1);
	mainLayout->addWidget(deathEdit,3,2);

	mainLayout->addWidget(infoLabel,4,0,1,3,Qt::AlignCenter);
	mainLayout->addWidget(infoText,5,0,3,3);




	portraitLabel = new QLabel;
	QImage img(tr(":/no_photo.jpg"));
	portraitLabel->setPixmap(QPixmap::fromImage(img.scaled(300,400)));
	portraitLabel->adjustSize();


	mainLayout->addWidget(portraitLabel,0,3,7,1);

	QPushButton * changePhoto = new QPushButton(tr("Изменить фотографию"));
	mainLayout->addWidget(changePhoto,7,3);

	connect(changePhoto,SIGNAL(pressed()),this,SLOT(changePic()));

	setLayout(mainLayout);
	setWindowTitle(tr("Профиль"));
	photoPath.asprintf(":/no_photo.jpg");
}

Info::Info(Person src)
{
	QLabel * nameLabel = new QLabel(tr("ФИО: "));
	fioEdit = new QLineEdit(src.getName());
	fioEdit->setFixedWidth(300);
	QLabel * birthLabel = new QLabel(tr("Дата Рождения: "));
	birthEdit = new QLineEdit(src.getBDate().toString());
	QLabel * infoLabel = new QLabel(tr("Информация:"));
	infoText = new QPlainTextEdit(src.getInfo());
	QGridLayout * mainLayout = new QGridLayout;

	QLabel * placeLabel = new QLabel(tr("Место Рождения: "));
	birthPlace = new QLineEdit(src.getBirthPlace());

	infoText->setMinimumHeight(300);

	QCheckBox * check = new QCheckBox(tr("Живой"));
	check->setChecked(1);
	QLabel * deadLabel = new QLabel(tr("Дата смерти: "));
	deathEdit = new QLineEdit(tr("01.01.1900"));


	mainLayout->addWidget(nameLabel,0,0,Qt::AlignLeft);
	mainLayout->addWidget(fioEdit,0,1,1,2,Qt::AlignRight);
	mainLayout->addWidget(birthLabel,1,0,Qt::AlignLeft);
	mainLayout->addWidget(birthEdit,1,1,1,2);
	mainLayout->addWidget(placeLabel,2,0,Qt::AlignLeft);
	mainLayout->addWidget(birthPlace,2,1,1,2);

	mainLayout->addWidget(check,3,0);
	mainLayout->addWidget(deadLabel,3,1);
	mainLayout->addWidget(deathEdit,3,2);

	mainLayout->addWidget(infoLabel,4,0,1,3,Qt::AlignCenter);
	mainLayout->addWidget(infoText,5,0,3,3);




	portraitLabel = new QLabel;
	QImage img(src.getPhotoPath());
	portraitLabel->setPixmap(QPixmap::fromImage(img.scaled(300,400)));
	portraitLabel->adjustSize();


	mainLayout->addWidget(portraitLabel,0,3,7,1);

	QPushButton * changePhoto = new QPushButton(tr("Изменить фотографию"));
	mainLayout->addWidget(changePhoto,7,3);

	connect(changePhoto,SIGNAL(pressed()),this,SLOT(changePic()));

	setLayout(mainLayout);
	setWindowTitle(tr("Профиль"));
	photoPath = src.getPhotoPath();
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
	photoPath = QFileDialog::getOpenFileName(this,
		 tr("Open Image"),"C:/", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
	QImage newpic(photoPath);
	portraitLabel->setPixmap(QPixmap::fromImage(newpic.scaled(300,400)));
	portraitLabel->adjustSize();
}


Person Info::export_data()
{
	return Person()	;


}





