#pragma once
#include <algorithm>
#include <iostream>
using namespace std;
class UnderflowException { };
static const int ALLOWED_IMBALANCE = 1;

template <typename T>
class AvlTree {
public:
	// default constructor
	AvlTree() : root{ nullptr } {}
	//copy constructors
	AvlTree(const AvlTree& rhs) : root{ nullptr } {
		root = clone(rhs.root);
	}
	//destructor
	~AvlTree() {
		makeEmpty(root);
	}

	AvlTree& operator= (const AvlTree& rhs) {
		AvlTree deepCopy = rhs;
		std::swap(*this, deepCopy);
		return *this;
	}



	/**
	* Print the tree contents in sorted order.
	*/
	void printTree() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printTree(root);
	}


	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(const T& x)
	{
		insert(x, root);
	}


	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove(const T& x)
	{
		remove(x, root);
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const
	{
		return root == nullptr;
	}


	/**
	 * Find a key in the tree.
	 * display Not found or found with left child' element (none if null) and right child's element (none if null).
	 */
	void findKey(const T& x) {
		AvlNode* node = root;

		while (node->element != x)
		{
			if (x < node->element)	// Key is less than current node's element
			{
				if (node->left == nullptr)
				{
					cout << "Not Found" << endl;
					return;
				}
				else
				{
					node = node->left;
				}
			}
			else	// Key is greater than current node's element
			{
				if (node->right == nullptr)
				{
					cout << "Not Found" << endl;
					return;
				}
				else
				{
					node = node->right;
				}
			}
		}

		cout << x << " found with ";

		if (node->left == nullptr)
			cout << "left child: null";
		else
			cout << "left child: " << node->left->element;

		cout << " and ";

		if (node->right == nullptr)
			cout << "right child: null";
		else
			cout << "right child: " << node->right->element;

		cout << endl;
	}

private:

	class AvlNode {
	public:
		AvlNode(const T& e, AvlNode* lt, AvlNode* rt, int h = 0)
			: element{ e }, left{ lt }, right{ rt }, height{ h } {}

		T element;
		AvlNode* left;
		AvlNode* right;
		int height;

		/*
		friend AvlNode& operator= (const AvlNode& r)
		{
		}

		*/
	};

	/*
	AvlNode& operator= (const AvlNode& r)
	{
		this->element = r->element;
		this->left = r->left;
		this->right = r->right;
	}

	*/
	AvlNode* root;
	/**
	  * Internal method to insert into a subtree.
	  * x is the item to insert.
	  * t is the node that roots the subtree.
	  * Set the new root of the subtree.
	  */
	void insert(const T& x, AvlNode*& t)
	{
		if (t == nullptr)
			t = new AvlNode{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);

		balance(t);
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove(const T& x, AvlNode*& t)
	{
		if (t == nullptr)
		{
			return;	// Empty tree, nothing to remove
		}
		else if (x < t->element)
		{
			remove(x, t->left);
		}
		else if (x > t->element)
		{
			remove(x, t->right);
		}
		else if ((t->left != nullptr) && (t->right != nullptr))
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			if (t->left != nullptr)
			{
				AvlNode* temp = t->left;

				t = t->left;

				delete temp;
			}
			else if (t->right != nullptr)
			{
				AvlNode* temp = t->right;

				t = t->right;

				delete temp;
			}
			else
			{
				delete t;
				t = nullptr;
			}
		}

		balance(t);
	}

	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance(AvlNode*& t)
	{
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		else
			if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
				if (height(t->right->right) >= height(t->right->left))
					rotateWithRightChild(t);
				else
					doubleWithRightChild(t);

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	AvlNode* findMin(AvlNode* t) const
	{
		if (t->left == nullptr)
			return t;

		return findMin(t->left);
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	AvlNode* findMax(AvlNode* t) const
	{
		if (t->right == nullptr)
			return t->element;

		return findMax(t->right);
	}



	/**
	* Internal method to make subtree empty.
	*/
	void makeEmpty(AvlNode*& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	// Internal method to print a subtree rooted at t in sorted order
	void printTree(AvlNode* t) const {
		if (t != nullptr) {
			printTree(t->left);
			cout << t->element << endl;
			printTree(t->right);
		}
	}

	/**
	* Internal method to return the height of node t or -1 if nullptr.
	*/
	int height(AvlNode* t) const
	{
		return t == nullptr ? -1 : t->height;
	}

	/**
	* Internal method to return the max value.
	*/
	int max(int lhs, int rhs) const
	{
		return lhs > rhs ? lhs : rhs;
	}
	/**
	* Internal method to clone subtree.
	*/
	AvlNode* clone(AvlNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
	}


	/**
 * Rotate binary tree node with left child.
 * For AVL trees, this is a single rotation for case 1.
 * Update heights, then set new root.
 */
	void rotateWithLeftChild(AvlNode*& k2)
	{
		AvlNode* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild(AvlNode*& k1)
	{
		AvlNode* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}

	/**
	 * Double rotate binary tree node: first left child.
	 * with its right child; then node k3 with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */
	void doubleWithLeftChild(AvlNode*& k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	/**
	 * Double rotate binary tree node: first right child.
	 * with its left child; then node k1 with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void doubleWithRightChild(AvlNode*& k1)
	{
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}
};