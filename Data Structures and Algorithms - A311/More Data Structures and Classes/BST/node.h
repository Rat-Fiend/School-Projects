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
	void setLeft(Node* next);
	void setRight(Node* next);
	void setParent(Node* next);
	Node<T>* getLeft();
	Node<T>* getRight();
	Node<T>* getParent();
private:
	T item;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
};

