// main.cpp
//
// Short test program for the linked list class.

#include <iostream>
#include <string>
#include "linkedlist.cpp"
#include "node.h"

using namespace std;

int main()
{
	DoublyLinkedList<string> dll;
	dll.insert("A");
	dll.insert("B");
	dll.insert("C");
	dll.insert("B");		// Second B
	dll.insert("Hi");

	dll.print();	// Hi,B,C,B,A

	cout << "Contains C? ";
	cout << (dll.find("C") == nullptr ? "No" : "Yes") << endl;		// Yes

	cout << "Contains D? ";
	cout << (dll.find("D") == nullptr ? "No" : "Yes") << endl;		// No

	// Tests
	dll.insertBefore(dll.getHead()->getItem(), "F");	// Inserts before head of list
	dll.print();

	dll.insertBefore("C", "H");							// Inserts item near middle of list
	dll.print();

	dll.deleteNode(dll.getHead()->getItem());			// Deletes head of list
	dll.print();

	dll.deleteNode("B");								// Deletes all nodes with item "B"
	dll.print();

	dll.deleteNode("Hi");								// Deletes tail of list
	dll.print();

}