#include "family.h"

Family::Family(Person * me)
{
	root = me;
	everybody.push_back(me);
}

void Family::addPerson(Person *new_el)
{
	everybody.push_back(new_el);
}

void Family::deletePerson(int num)
{
	everybody.remove(num);
}

