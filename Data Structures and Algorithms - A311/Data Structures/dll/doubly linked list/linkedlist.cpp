// linkedlist.cpp
//
// Implementation of a doubly linked list using templates.
//
#include <iostream>
#include "linkedlist.h"
using namespace std;

// Initialize the head to nullptr
template<class T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr)
{
}

// When this linked list goes out of scope, delete all the nodes in the list
template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	Node<T>* temp = head;
	while (head != nullptr)
	{
		temp = head;
		head = head->getNext();
		delete temp;
	}
}

// Inserts a new node at the front of the list
template<class T>
void DoublyLinkedList<T>::insert(T item)
{
	Node<T>* node = new Node<T>(item);
	node->setNext(head);
	if (head != nullptr)
		head->setPrev(node);
	head = node;
}

// **** Insert a new node before the node containing the target
template<class T>
void DoublyLinkedList<T>::insertBefore(const T& target, const T& newItem)
{
	if ((target == head->getItem()) || (head == nullptr))	// Inserting before head or into empty list
	{
		insert(newItem);
	}
	else
	{
		Node<T>* after = find(newItem);
		Node<T>* before = after->getPrev();
		Node<T>* temp = new Node(newItem);

		before->setNext(temp);		// Set next
		temp->setNext(after);

		after->setPrev(temp);	// Set previous
		temp->setPrev(before);
	}
}

// Searches the linked list for item.
// For this to work, == must be overloaded for the template item.
// If the item is not found, nullptr is returned.
// Otheriwse, a pointer to the found node is returned.
template<class T>
Node<T>* DoublyLinkedList<T>::find(T item)
{
	Node<T>* temp = head;
	while (temp != nullptr)
	{
		if (temp->getItem() == item)
			return temp;
		temp = temp->getNext();
	}
	return nullptr;
}

// Loop through the linked list and output each item.
// For this to work properly on all template classes, the
// << operator should be overloaded for the class.
template<class T>
void DoublyLinkedList<T>::print()
{
	Node<T>* temp = head;
	cout << endl;
	while (temp != nullptr)
	{
		cout << temp->getItem() << endl;
		temp = temp->getNext();
	}
	cout << endl;
}

// Return pointer to head of list
template<class T>
Node<T>* DoublyLinkedList<T>::getHead()
{
	return head;
}


// Delete all nodes containing target.
template<class T>
void DoublyLinkedList<T>::deleteNode(const T& target)
{
	while (find(target) != nullptr)
	{
		Node<T>* temp = find(target);

		if (temp == head)	// Deleting haed of list
		{
			Node<T>* newHead = head->getNext();
			newHead->setPrev(head->getPrev());
			delete head;
			head = newHead;
		}
		else if (temp->getNext() == nullptr)	// Last element of list
		{
			Node<T>* newTail = temp->getPrev();
			newTail->setNext(nullptr);
			delete temp;
		}
		else
		{
			Node<T>* prevTemp = temp->getPrev();
			Node<T>* nextTemp = temp->getNext();

			prevTemp->setNext(nextTemp);
			nextTemp->setPrev(prevTemp);

			delete temp;
		}
	}
}