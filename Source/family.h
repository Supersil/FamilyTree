#ifndef FAMILY_H
#define FAMILY_H

#include <QObject>
#include "person.h"
#include <QVector>

class Family
{
public:
	explicit Family(Person * me);
	void addPerson(Person * new_el);
	void deletePerson(int num);

private:
	Person * root;
	QVector<Person *> everybody;

};

#endif // FAMILY_H
