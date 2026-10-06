// Written by Quinton Odenthal

#include <iostream>
#include "Pair.h"

using namespace std;

Pair operator+(int num, Pair e)
{
	Pair temp(e.num1, e.num2);
	temp.num1 += num;
	temp.num2 += num;
	return temp;
}

Pair operator+(const Pair& e1, const Pair& e2)
{
	Pair newPair(e1.num1, e1.num2);
	newPair.num1 += e2.num1;
	newPair.num2 += e2.num2;
	return newPair;
}

int main()
{
	Pair p1(5, 10);
	Pair p2(1, 2);
	// Outputs 5 and 10
	cout << p1.get1() << " " << p1.get2() << endl;
	// Outputs 1 and 2
	cout << p2.get1() << " " << p2.get2() << endl;
	Pair p3 = p2 + p1;
	// Outputs 6 and 12
	cout << p3.get1() << " " << p3.get2() << endl;
	p3 = 2 + p3; // Doesn't work because the operand+ def is expecting a Pair object as the calling object and an int as the passed object
	// Outputs 8 and 14
	cout << p3.get1() << " " << p3.get2() << endl;
}