#include "Person.h"
#include <string>

using namespace std;

Person::Person()
{
	name = "Jon Doe";
	age = 0;
}

Person::Person(string n, int a)
{
	name = n;
	age = a;
}

Person::~Person()
{

}

void Person::setName(string n)
{
	name = n;
}

string Person::getName()
{
	return name;
}

void Person::setAge(int a)
{
	age = a;
}

int Person::getAge()
{
	return age;
}

ostream& operator<<(ostream& os, Person const t)
{
	cout << t.name;
	return os;
}

bool operator<(Person const c1, Person const c2)
{
	if (c1.name < c2.name)
		return true;
	else
		return false;
}

bool operator>(Person const c1, Person const c2)
{
	if (c1.name > c2.name)
		return true;
	else
		return false;
}

bool operator==(Person const c1, Person const c2)
{
	if (c1.name == c2.name)
		return true;
	else
		return false;
}
