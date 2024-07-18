#include <stdio.h>
#include "AvlTree.h"
#include <iostream>

using namespace std;

int main()
{
	AvlTree<int> avl;

	avl.insert(5);
	avl.insert(2);
	avl.insert(8);
	avl.insert(1);
	avl.insert(7);
	avl.insert(4);
	avl.insert(3);

	cout << "Check all the elements and their children:" << endl;
	avl.findKey(1);
	avl.findKey(2);
	avl.findKey(4);
	avl.findKey(3);
	avl.findKey(5);
	avl.findKey(8);
	avl.findKey(7);

	cout << endl;

	avl.insert(6);

	cout << "After inserting 6" << endl;

	avl.findKey(1);
	avl.findKey(2);
	avl.findKey(4);
	avl.findKey(3);
	avl.findKey(5);
	avl.findKey(8);
	avl.findKey(7);
	avl.findKey(6);

	cout << endl;

	avl.remove(6);

	cout << "After removing 6" << endl;

	avl.findKey(1);
	avl.findKey(2);
	avl.findKey(4);
	avl.findKey(3);
	avl.findKey(5);
	avl.findKey(8);
	avl.findKey(7);

	return 0;
}