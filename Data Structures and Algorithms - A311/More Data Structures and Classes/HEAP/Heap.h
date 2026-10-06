#pragma once

using namespace std;

template <class T>
class Heap {
private:
    static const int HEAPSIZE = 31;
    T array[HEAPSIZE];  // 1-based array
    int numElements = 0;

public:
    Heap();
    ~Heap();
    void insert(T p);
    int getHeapsize();
    T extractMax();
    void heapify(int i);

};