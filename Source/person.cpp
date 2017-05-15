#include "person.h"

int Person::global_id;

Person::Person()
{
	birthDate.currentDate();
	isAlive = true;
	deathDate.setDate(0,0,0);
	name.sprintf("Фамилия Имя Отчество");
	father = 0;
	mother = 0;
	children.clear();
	id = new_id();
	info.sprintf("Информация о человеке");
	birthPlace.sprintf("Населённый пункт");
}


Person::~Person()
{

}

Person::Person(QDate birth, QDate death, bool alive, QString n_name, QString n_info, QString n_birthPlace, QString photopath)
{
	birthDate = birth;
	deathDate = death;
	isAlive = alive;
	name = n_name;
	father = 0;
	mother = 0;
	children.clear();
	id = new_id();
	info = n_info;
	birthPlace = n_birthPlace;
	photoPath = photopath;
}

Person::Person(QDate birth, QString n_name, QString n_info, QString n_birthPlace, QString photopath)
	: info(n_info), birthPlace(n_birthPlace),photoPath(photopath)
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

QDate Person::getBDate()
{
	return birthDate;
}

QString Person::getInfo()
{
	return info;
}

QDate Person::getDDate()
{
	return deathDate;
}

QString Person::getBirthPlace()
{
	return birthPlace;
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

Person * Person::mom()
{
	return mother;
}

Person * Person::dad()
{
	return father;
}

int Person::children_num()
{
	return children.size();
}

Person * Person::child(int num)
{
	return children[num];
}

QString Person::getPhotoPath()
{
	return photoPath;
}






