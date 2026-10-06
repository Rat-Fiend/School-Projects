// node.h
//
// This is a template class that stores a node in a doubly linked list. 
// The variable "item" holds the payload data for the node.
// The variable next is a pointer to the next node in the list, or nullptr if at the end.
// The variable prev is a pointer to the previous node in the list, or nullptr if at the front.

//
// For scalability, it would be best if the class implementing the template overloads 
// the << operator and the == operator so they can be output or compared.

#pragma once
#include <iostream>
using namespace std;

template<class T>
class Node
{
public:
	Node();
	Node(T item);
	~Node();
	T& getItem();
	void setNext(Node* next);
	Node<T>* getNext();
	void setPrev(Node* prev);
	Node<T>* getPrev();
private:
	T item;
	Node<T>* next;
	Node<T>* prev;
};

