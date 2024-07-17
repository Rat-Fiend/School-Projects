#include <iostream>
#include "node.h"

template<class T>
Node<T>::Node()
{
 left = nullptr;
 right = nullptr;
 parent = nullptr;
}

template<class T>
Node<T>::Node(T item) : item(item)
{
 left = nullptr;
 right = nullptr;
 parent = nullptr;
}

template<class T>
Node<T>::~Node()
{
}

template<class T>
Node<T>* Node<T>::getLeft()
{
  return left;
}

template<class T>
Node<T>* Node<T>::getRight()
{
  return right;
}

template<class T>
Node<T>* Node<T>::getParent()
{
  return parent;
}

template<class T>
void Node<T>::setLeft(Node *n)
{
  left = n;
}

template<class T>
void Node<T>::setRight(Node *n)
{
  right = n;
}

template<class T>
void Node<T>::setParent(Node *n)
{
  parent = n;
}

template<class T>
T& Node<T>::getItem()
{
  return item;
}

