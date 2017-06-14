#include "person.h"

int Person::global_id;

Person::Person()
{
	birthDate.currentDate();
	isAlive = true;
	deathDate.setDate(0,0,0);
	name.sprintf("Фамилия Имя Отчество");
	father = nullptr;
	mother = nullptr;
	children.clear();
	id = new_id();
	info.sprintf("Информация о человеке");
	birthPlace.sprintf("Населённый пункт");
	set = false;
}

Person::Person(const Person &src)
{
	birthDate = src.birthDate;
	isAlive = src.isAlive;
	deathDate = src.deathDate;
	name = src.name;
	father = src.father;
	mother = src.mother;
	children = src.children;
	id = new_id();
	info = src.info;
	birthPlace = src.birthPlace;
	set = true;
}

Person::~Person()
{

}

Person::Person(QDate birth, QDate death, bool alive, QString n_name, QString n_info, QString n_birthPlace, QString photopath, sexx s)
{
	birthDate = birth;
	deathDate = death;
	isAlive = alive;
	name = n_name;
	father = nullptr;
	mother = nullptr;
	children.clear();
	id = new_id();
	info = n_info;
	birthPlace = n_birthPlace;
	photoPath = photopath;
	set = true;
	sex = s;
}

Person::Person(QDate birth, QString n_name, QString n_info, QString n_birthPlace, QString photopath, sexx s)
	: info(n_info), birthPlace(n_birthPlace),photoPath(photopath)
{
	birthDate = birth;
	deathDate.setDate(0,0,0);
	isAlive = true;
	name = n_name;
	father = nullptr;
	mother = nullptr;
	children.clear();
	id = new_id();
	set = true;
	sex = s;
}

void Person::setFather(Person *dad)
{
	father = dad;
}

void Person::setMother(Person *mom)
{
	mother = mom;
}

sexx Person::getSex()
{
	return sex;
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

bool Person::checkAlive()
{
	return isAlive;
}

void Person::import_data(Person * profile)
{

	birthDate = profile->getBDate();
	deathDate = profile->getDDate();
	isAlive = profile->checkAlive();
	name = profile->getName();
	info = profile->getInfo();
	birthPlace = profile->getBirthPlace();
	photoPath = profile->getPhotoPath();
	father = profile->dad();
	mother = profile->mom();
	sex = profile->getSex();
	children.clear();
	for(int i=0; i < profile->children_num(); i++)
		children.append(profile->child(i));
	delete profile;
	set = true;
}


void Person::save_pure(QString filename)
{
	QFile ofile;
	ofile.setFileName(filename);
	ofile.open(QIODevice::WriteOnly | QIODevice::Text);
	if (!ofile.isOpen())
	{
		QMessageBox warning;
		warning.setText("Error while opening the output file!");
		warning.setInformativeText(filename);
		warning.setWindowTitle("Error");
		warning.exec();
		return;
	}
	/*
		save structure:
		id
		Name
		1/0(alive) birthdate deathdate(even if alive)
		sex(M/F)
		mom_id dad_id
		number_of_children child1_id child2_id ...
		birthPlace
		/!info!\
		Info...
		\!info!/

	*/

	QTextStream out(&ofile);
	out << id << endl << name << endl;
	out << isAlive << ' ' << birthDate.toString("dd.MM.yyyy")
			<< ' ' << deathDate.toString("dd.MM.yyyy") << endl;
	out << ((sex==MALE)?'M':'F') << endl;
	out << ((mother!=nullptr)? mother->get_id() : -1) << ' ';
	out << ((father!=nullptr)? father->get_id() : -1) << endl;
	out << children.size() << ' ';
	for(auto it: children)
		out << it->get_id() << ' ';
	out << endl;
	out << birthPlace << endl;
	out << "/!info!\\" << endl;
	out << info << endl;
	out << "\\!info!/" << endl << endl;

	ofile.close();

}


