#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QDate>
#include <QString>
#include <QVector>

class Person
{
private:
	QDate birthDate;
	QDate deathDate;
	bool isAlive;
	QString name;
	QString info;
	QString birthPlace;
	QString photoPath;

	Person * father;
	Person * mother;
	QVector<Person*> children;
	int id;
	static int global_id;
	int new_id();

public:
	Person();
	~Person();
	Person(QDate birth, QDate death, bool alive, QString n_name, QString n_info, QString n_birthPlace, QString photopath);
	Person(QDate birth, QString n_name, QString n_info, QString n_birthPlace, QString photopath);
	void setParents(Person * dad, Person * mom);
	QString getName();
	void addChild(Person * child);
	int get_id();
	QDate getBDate();
	QDate getDDate();
	QString getBirthPlace();
	QString getInfo();
	int children_num();
	Person * mom();
	Person * dad();
	Person * child(int num);
	QString getPhotoPath();
};

#endif // PERSON_H
