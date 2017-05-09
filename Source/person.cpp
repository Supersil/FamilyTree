#include "person.h"

int Person::global_id;

Person::Person()
{
	birthDate.currentDate();
	isAlive = true;
	deathDate.setDate(0,0,0);
	name.sprintf("Иванов Иван Иванович");
	father = 0;
	mother = 0;
	children.clear();
	id = new_id();
}

Person::~Person()
{

}

Person::Person(QDate birth, QDate death, bool alive, QString n_name)
{
	birthDate = birth;
	deathDate = death;
	isAlive = alive;
	name = n_name;
	father = 0;
	mother = 0;
	children.clear();
	id = new_id();
}

Person::Person(QDate birth, QString n_name)
{
	birthDate = birth;
	deathDate.setDate(0,0,0);
	isAlive = true;
	name = n_name;
	father = 0;
	mother = 0;
	children.clear();
	id = new_id();
}

QString Person::getName()
{
	return name;
}

void Person::addChild(Person *child)
{
	children.append(child);
}

int Person::new_id()
{
	return global_id++;
}

int Person::get_id()
{
	return id;
}



