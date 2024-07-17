#pragma once
#include <string>
using namespace std;

class Movie
{
private:
	string name;
	string rating;
public:
	Movie();
	Movie(string newName, string newRating);

	string getName();
	string getRating();

	string getNameLower();

	// friend void operator==(Movie m1, Movie m2);
};

