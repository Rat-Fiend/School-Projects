#include "bst.cpp"
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

/*
void createRandBST(int size);

void createRandBST(int size)
{
	BST<int> bst;

	for (int i = 0; i < size; i++)
	{
		bst.insert(rand() % 20);
	}

	bst.traverse();

	cout << "BST going out of scope, should start destructing itself." << endl;
}
*/


int main()
{
	srand(time(NULL));

	BST<int> maxHeap;
	maxHeap.buildMaxHeap();
	maxHeap.isMax();

	BST<int> maxHeap1;
	maxHeap1.buildMaxHeap();
	maxHeap1.isMax();

	BST<int> notMaxHeap;
	notMaxHeap.insert(rand() % 100);
	notMaxHeap.insert(rand() % 100);
	notMaxHeap.insert(rand() % 100);
	notMaxHeap.insert(rand() % 100);
	notMaxHeap.insert(rand() % 100);
	notMaxHeap.insert(rand() % 100);
	notMaxHeap.insert(rand() % 100);
	notMaxHeap.isMax();

	BST<int> notMaxHeap1;
	notMaxHeap1.insert(rand() % 100);
	notMaxHeap1.insert(rand() % 100);
	notMaxHeap1.insert(rand() % 100);
	notMaxHeap1.insert(rand() % 100);
	notMaxHeap1.insert(rand() % 100);
	notMaxHeap1.insert(rand() % 100);
	notMaxHeap1.insert(rand() % 100);
	notMaxHeap1.isMax();

	/*
	Node<int> *temp = bst.find(5);
	bst.deleteNode(temp);
	temp = bst.find(7);
	bst.deleteNode(temp);
	temp = bst.find(5);
	bst.deleteNode(temp);

	cout << "Traversing tree in-order" << endl;
	bst.traverse();
	cout << endl;
	*/



	return 0;
}