#include "Pair.h"

Pair::Pair() : num1(0), num2(0)
{
}

Pair::Pair(int num1, int num2) : num1(num1), num2(num2)
{
}

int Pair::get1()
{
	return num1;
}

int Pair::get2()
{
	return num2;
}