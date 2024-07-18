// Entire code written by Quinton Odenthal

#include <iostream>

using namespace std;

void addOne(int* ptrNum);


void addOne(int* ptrNum)
{
	*ptrNum = *ptrNum + 1;
}


int main()
{
	int num = 5;

	cout << "Starting num: " << num << endl;

	addOne(&num);

	cout << "Incremented num: " << num << endl;

	return 0;
}
