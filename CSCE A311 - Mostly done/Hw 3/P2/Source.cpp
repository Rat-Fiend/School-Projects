#include "Heap.h"
#include "Person.h"
#include <iostream>

using namespace std;

int main()
{
	Heap<Person> personHeap;

	personHeap.insert(Person("Abe", 60));
	personHeap.insert(Person("Burt", 10));
	personHeap.insert(Person("Charles", 72));
	personHeap.insert(Person("Denis", 6));
	personHeap.insert(Person("Sam", 100));
	personHeap.insert(Person("Yen", 30));

	for (int i = 0; i < 6; ++i)
	{
		cout << personHeap.extractMax() << endl;
	}




	return 0;
}