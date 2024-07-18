// Written by Quinton Odenthal

#include <iostream>
#include "Movie.h"

using namespace std;

void sort(Movie list[], int len);
void swapMovie(Movie &m1, Movie &m2);
void printMovieList(Movie list[], int len);

int main()
{
	const int LIST_LEN = 6;

	Movie movieList[LIST_LEN] =
	{
		Movie("Black Panther", "PG - 13"),
		Movie("Avengers: Infinity War", "PG - 13"),
		Movie("A Wrinkle In Time", "PG"),
		Movie("Ready Player One", "PG - 13"),
		Movie("Red Sparrow", "R"),
		Movie("The Incredibles 2", "G")
	};

	sort(movieList, LIST_LEN);

	printMovieList(movieList, LIST_LEN);

	return 0;
}

void swapMovie(Movie& m1, Movie& m2)
{
	Movie temp;
	temp = m1;
	m1 = m2;
	m2 = temp;
}

void sort(Movie list[], int len)
{
	for (int i = 1; i < len; i++)
	{
		if (list[i - 1].getNameLower().compare(list[i].getNameLower()) > 0)
		{
			swapMovie(list[i - 1], list[i]);
		};
	};
}

void printMovieList(Movie list[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << list[i].getName() << ", " << list[i].getRating() << endl;
	}
}