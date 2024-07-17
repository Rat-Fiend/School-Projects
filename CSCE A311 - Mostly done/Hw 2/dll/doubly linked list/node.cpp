// node.cpp
//
// Simple implementation of node.h.

#include <iostream>
#include "node.h"

template<class T>
Node<T>::Node() : next(nullptr), prev(nullptr)
{
}

template<class T>
Node<T>::Node(T item) : item(item)
{
}

template<class T>
Node<T>::~Node()
{
}

template<class T>
Node<T>* Node<T>::getNext()
{
	return next;
}

template<class T>
void Node<T>::setNext(Node* n)
{
	next = n;
}

template<class T>
Node<T>* Node<T>::getPrev()
{
	return prev;
}

template<class T>
void Node<T>::setPrev(Node* p)
{
	prev = p;
}

template<class T>
T& Node<T>::getItem()
{
	return item;
}

