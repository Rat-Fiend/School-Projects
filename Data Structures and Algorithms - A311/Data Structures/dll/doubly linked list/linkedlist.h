// linkedlist.h
//
// Template implementation of doubly linked lists.  This in turn uses the
// template class Node<T> to store the data and the link to the next/prev node.
//
// Insert will insert onto the front of the list.
#pragma once

#include <iostream>
#include "node.cpp"  // Including cpp file instead of .h because of templates
using namespace std;

template<class T>
class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void insertBefore(const T& target, const T& newItem);  // **** New function to write
	void insert(T item);  // Inserts at the front of the list only
	void deleteNode(const T& target);  // **** New function to write
	Node<T>* find(T item);  // Returns node if item is found
	void print(); // Print all items in the list
	Node<T>* getHead();	// Return pointer to head of list
private:
	Node<T>* head;
};

