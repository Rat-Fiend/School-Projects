#include "Heap.h"
#include <iostream>
#include <array>

using namespace std;

template<class T>
Heap<T>::Heap()
{
	numElements = 0;
}

template<class T>
Heap<T>::~Heap()
{
    for (int i = 0; i < HEAPSIZE; ++i)
    {
        delete array[i];
    }
    delete array;
}

template<class T>
void Heap<T>::insert(T p)
{
	int size = numElements + 1;
	int i = size;

	while ((i > 1) && (array[i / 2] < p))
	{
		array[i] = array[i / 2];
		i = i / 2;
	}
	array[i] = p;

	numElements++;
}

template<class T>
int Heap<T>::getHeapsize()
{
	return HEAPSIZE;
}

template<class T>
T Heap<T>::extractMax()
{
    T temp = array[1];  // Largest element
    array[1] = array[numElements];   // Last element of list
    delete array[numElements];
    numElements--;
    heapify(1);
    return temp;
}

template<class T>
void Heap<T>::heapify(int i)
{
    int largest = i;    // Initialize largest as root
    int left = 2 * i;   // Formula for 1 - based array
    int right = 2 * i + 1;
    int heapSize = numElements;

    if ((left < heapSize) && (array[left] > array[largest]))
    {
        largest = left;
    }

    if ((right < heapSize) && (array[right] > array[largest]))
    {
        largest = right;
    }

    if (largest != i)
    {
        T temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        heapify(largest);
    }
}
