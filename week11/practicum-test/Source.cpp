#include <iostream>
#include <cassert>

#include "Person.h"
#include "Group.h"

int main()
{
	Person p1("Ivan", nullptr, "Ivanov", "0148785600");
	Person p2("Petar", "Petrov", "9987456852");
	Person p3("Nikola", "Georgiev", "Chakalov", "9524151578");

	Group myGroup;
	myGroup += p1;
	myGroup += p1;
	myGroup += p1;

	assert(myGroup() == 1);

	myGroup += p2;

	Group otherGroup = myGroup + p3;

	assert(myGroup() == otherGroup() - 1);

	myGroup -= p1;
	myGroup -= p1;
	myGroup -= p1;

	assert(myGroup() == 1);

	assert(strcmp(myGroup["9987456852"].getFirstName(), "Petar") == 0);
}