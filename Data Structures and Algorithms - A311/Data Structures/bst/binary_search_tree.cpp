#include "bst.cpp"
#include <iostream>

using namespace std;

int main()
{
  BST<int> bst;
  bst.insert(5);
  bst.insert(3);
  bst.insert(2);
  bst.insert(5);
  bst.insert(7);
  bst.insert(8);

  Node<int> *temp = bst.find(5);
  bst.deleteNode(temp);
  temp = bst.find(7);
  bst.deleteNode(temp);
  temp = bst.find(5);
  bst.deleteNode(temp);

  cout << "Traversing tree in-order" << endl;
  bst.traverse();
  cout << endl;


  return 0;
}


