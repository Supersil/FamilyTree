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

	Person * father;
	Person * mother;
	QVector<Person*> children;
	int id;
	static int global_id;
	int new_id();

public:
	Person();
	~Person();
	Person(QDate birth, QDate death, bool alive, QString n_name);
	Person(QDate birth, QString n_name);
	void setParents(Person * dad, Person * mom);
	QString getName();
	void addChild(Person * child);
	int get_id();

};

#endif // PERSON_H
