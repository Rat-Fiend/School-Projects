#include "Movie.h"
using namespace std;

Movie::Movie() : name("unnamed"), rating("not rated") {};

Movie::Movie(string newName, string newRating) :
	name(newName), rating(newRating) {};

string Movie::getName()
{
	return name;
};

string Movie::getRating()
{
	return rating;
};

string Movie::getNameLower()
{
	string temp = name;
	for (int i = 0; i < temp.length(); i++)
	{
		temp[i] = tolower(temp[i]);
	}

	return temp;
}

/*
void operator+(Movie m1, Movie m2)
{
	m1.name = m2.name;
	m1.rating = m2.rating;
}
*/
