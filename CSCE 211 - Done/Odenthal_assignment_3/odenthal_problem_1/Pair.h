#pragma once
class Pair
{
private:
	int num1, num2;
public:
	Pair();
	Pair(int num1, int num2);
	int get1();
	int get2();
	friend Pair operator+(const Pair& e1, const Pair& e2);
	friend Pair operator+(int num, Pair e);
};