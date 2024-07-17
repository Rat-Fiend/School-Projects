// Code authored by Quinton Odenthal is marked
// Everyhting else should be assumed as boilerplate from a professor

#include <iostream>
using namespace std;

// Function prototypes
void swap(int &x, int &y);
void selectionSort(int a[], int startIndex, int endIndex);


// Written By: Quinton Odenthal #############
void swap(int &x, int &y) {
	int temp;
	temp = x;
	x = y;
	y = temp;
}
// ##########################################

// Recursively sort array a.
// startIndex: The index of the starting element in array a where we want sorting to begin.
//             For example, startIndex would be 0 to start at the first element.
// endIndex:   The index of the last element in array a where we want sorting to end.
//             For example, in an array of length 5, this would be 4 to specify the last element.
void selectionSort(int a[], int startIndex, int endIndex)
{
  // Base case or termination condition: quit if start and end are the same.
  // This would specify to sort only a single element, which is already sorted.
  if (startIndex == endIndex)
	return;

  int indexOfMin = startIndex;
  // Write code below that finds the index of the smallest value in the array from
  // startIndex +1   to  endIndex,  inclusive.
  // The variable indexOfMin should contain the index of this position.  For example, if
  // startIndex=3, endIndex=7, then if the smallest value in the array from a[4],a[5],a[6], and a[7]
  // is at index 5, then indexOfMin should get set to 5


  // Written By: Quinton Odenthal #############
  for (int i= startIndex + 1; i<=endIndex; ++i) {
	  if (a[i] < a[indexOfMin]) {
	  	indexOfMin = i;
	  }
  }
  // ##########################################


  // Once indexOfMin is found, swap the values in the array at indexOfMin and startIndex
  swap(a[indexOfMin], a[startIndex]);  // You have to write the swap function. See lecture notes.

  // Complete the recursive call below so it only sorts the array from startIndex+1 to endIndex
  selectionSort(a, startIndex + 1, endIndex);
}



// Write the swap function so it swaps integers x and y by reference
// See lecture notes


// Write the main function with a test case of selectionSort

// Written By: Quinton Odenthal ###############################

int main() {
	int const ARRAY_LENGTH = 10;
	int a[ARRAY_LENGTH] = {15, 2, 4, 78, 94, 47, 1, 5, 85, 34};

	cout << "Unsorted array: ";
	for (int i=0; i<ARRAY_LENGTH; ++i) {
		cout << a[i] << " ";
	}
	cout << endl << endl;

	selectionSort(a, 0, ARRAY_LENGTH - 1);

	cout << "Sorted array: ";
        for (int i=0; i<ARRAY_LENGTH; ++i) {
                cout << a[i] << " ";
        }
        cout << endl << endl;

	return 0;
}
// ############################################################
