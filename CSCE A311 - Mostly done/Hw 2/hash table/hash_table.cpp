#include <iostream>
#include <vector>

using namespace std;
const int TABLESIZE = 31;

//hash function defined as modulo operator
//receive an item key and return bucket index
template<typename T>
int hfun(T key)
{
	return key % TABLESIZE;
}

//insert an item in the hash table
//Collision resolution by Linear Probing
// retuns the number of collisions when inserting the key
template<typename T>
int hashInsertLprobe(vector<T>& h, T key)
{
	int index = hfun(key);
	int collisions = 0;

	while (h[index] != -1)	// While the index location of vector is filled
	{
		collisions++;

		if (index == TABLESIZE - 1)	// Index is last spot in vector
		{
			index = 0;
		}
		else
		{
			index++;	// Tries next spot in vector
		}
	}

	h[index] = key;

	return collisions;
}

template<typename T>
void printHashTable(vector<T>h)
{
	cout << "Hash table after insertion:" << endl;

	for (int i = 0; i < TABLESIZE; i++)
	{
		cout << h[i] << " ";
	}
	cout << endl;
}

//hash insert, quadratic probing
// retuns the number of collisions when inserting the key
template<typename T>
int hashInsertQ(vector<T>& h, T key)
{
	int collisions = 0;
	int index = hfun(key);
	int temp = index;
	int x = 1;

	while (h[temp] != -1)	// While the index location of vector is filled
	{
		collisions++;
		temp = (index + (x * x)) % TABLESIZE;
		x++;
	}

	h[temp] = key;

	return collisions;
}

int main()
{
	vector<int> hTableL(TABLESIZE, -1); //initialize the hash table (all cells set to -1)
	vector<int> hTableq(TABLESIZE, -1);
	int collisionCountL = 0;
	int collisionCountQ = 0;
	int x;
	cout << "Integers inserted into the hash:\n";
	for (int i = 0; i < 20; i++)
	{
		x = rand() % 101; //random integer between 0 and 100
		cout << x << "  "; // print list
		//insret key into the hash and increment collisions
		collisionCountL += hashInsertLprobe(hTableL, x);
		collisionCountQ += hashInsertQ(hTableq, x);
	}
	cout << endl;
	cout << "number of collisions for Linear probing: " << collisionCountL << endl;
	printHashTable(hTableL);
	cout << endl;
	cout << "number of collisions for quadratic probing: " << collisionCountQ << endl;
	printHashTable(hTableq);
	system("pause");
	return 0;
}

