#include "info.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QCheckBox>

Info::Info(Person* src, QWidget * parent): QDialog(parent)
{
	if (src==0)
		src = new Person(QDate::currentDate(),tr("Иванов Иван Иванович"),
						 tr("Вырос, родился, женился..."),tr("Москва"),tr(":/no_photo.jpg"),MALE);

	QLabel * nameLabel = new QLabel(tr("ФИО: "));
	fioEdit = new QLineEdit(src->getName());
	fioEdit->setFixedWidth(300);
	QLabel * birthLabel = new QLabel(tr("Дата Рождения: "));
	birthEdit = new QLineEdit(src->getBDate().toString(tr("dd.MM.yyyy")));
	QLabel * infoLabel = new QLabel(tr("Информация:"));
	infoText = new QPlainTextEdit(src->getInfo());
	QGridLayout * mainLayout = new QGridLayout;

	QLabel * placeLabel = new QLabel(tr("Место Рождения: "));
	birthPlace = new QLineEdit(src->getBirthPlace());

	infoText->setMinimumHeight(300);

	aliveCheck = new QCheckBox(tr("Живой"));
	aliveCheck->setChecked(true);

	QLabel * deadLabel = new QLabel(tr("Дата смерти: "));
	deathEdit = new QLineEdit(tr("01.01.1900"));
	deathEdit->setDisabled(true);
	connect(aliveCheck,SIGNAL(clicked(bool)),deathEdit,SLOT(setDisabled(bool)));

	if (!src->checkAlive())
	{
		aliveCheck->setChecked(0);
		deathEdit->setEnabled(1);
		deathEdit->setText(src->getDDate().toString(tr("dd.MM.yyyy")));
	}

	mainLayout->addWidget(nameLabel,0,0,Qt::AlignLeft);
	mainLayout->addWidget(fioEdit,0,1,1,2,Qt::AlignRight);
	mainLayout->addWidget(birthLabel,1,0,Qt::AlignLeft);
	mainLayout->addWidget(birthEdit,1,1,1,1);

	sexBox = new QComboBox;
	sexBox->addItem("Мужской пол");
	sexBox->addItem("Женский пол");

	if (src->getSex()==MALE)
		sexBox->setCurrentIndex(0);
	else
		sexBox->setCurrentIndex(1);

	mainLayout->addWidget(sexBox,1,2);

	mainLayout->addWidget(placeLabel,2,0,Qt::AlignLeft);
	mainLayout->addWidget(birthPlace,2,1,1,2);

	mainLayout->addWidget(aliveCheck,3,0);
	mainLayout->addWidget(deadLabel,3,1);
	mainLayout->addWidget(deathEdit,3,2);

	mainLayout->addWidget(infoLabel,4,0,1,3,Qt::AlignCenter);
	mainLayout->addWidget(infoText,5,0,3,3);




	portraitLabel = new QLabel;
	QImage img(src->getPhotoPath());
	portraitLabel->setPixmap(QPixmap::fromImage(img.scaled(300,400)));
	portraitLabel->adjustSize();


	mainLayout->addWidget(portraitLabel,0,3,7,1);

	QPushButton * changePhoto = new QPushButton(tr("Изменить фотографию"));
	mainLayout->addWidget(changePhoto,7,3);

	QPushButton * saveBtn = new QPushButton(tr("Сохранить и закрыть профиль"));
	saveBtn->setFixedSize(200,30);
	mainLayout->addWidget(saveBtn,8,0,1,4,Qt::AlignCenter);

	connect(changePhoto,SIGNAL(pressed()),this,SLOT(changePic()));
	connect(saveBtn,SIGNAL(pressed()),this,SLOT(saveAndClose()));
	setLayout(mainLayout);
	setWindowTitle(tr("Профиль"));
	photoPath = src->getPhotoPath();

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

	if (photoPath.size()==0)
		photoPath.append(tr(":/no_photo.jpg"));
	QImage newpic(photoPath);
	portraitLabel->setPixmap(QPixmap::fromImage(newpic.scaled(300,400)));
	portraitLabel->adjustSize();
}


void Info::export_data()
{
	QDate birth = QDate::fromString(birthEdit->text(),"dd.MM.yyyy");
	QDate death = QDate::fromString(deathEdit->text(),"dd.MM.yyyy");
	bool alive = aliveCheck->isChecked();
	QString name = fioEdit->text();
	QString info = infoText->toPlainText();
	QString birthplace = birthPlace->text();
	QString photopath = photoPath;
	sexx sex;
	if (sexBox->currentText().contains("Муж"))
		sex = MALE;
	else
		sex = FEMALE;

	Person * profile = new Person(birth,death,alive,name,info,birthplace,photopath,sex);

	emit export_person(profile);

}

void Info::saveAndClose()
{
	export_data();
	close();
}





