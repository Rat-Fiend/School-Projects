// Entire code written by Quinton Odenthal

#include <iostream>

using namespace std;

bool isSorted(int arr[], int n);

bool isSorted(int arr[], int n) {
	if (n == 1)
	{
		return true;
	}

	if (arr[n-2] > arr[n-1])
	{
		return false;
	}
	else
	{
		return isSorted(arr, n-1);
	}
}

int main()
{
	const int ARRAY_LEN = 5;
	int sortedArr[ARRAY_LEN] = {1,2,3,4,5};
	int nonSortedArr[ARRAY_LEN] = {1,2,6,3,1};

	if (isSorted(sortedArr, ARRAY_LEN))
	{
		cout << "Sorted array is sorted" << endl;
	}
	else
	{
		cout << "Sorted array is not sorted" << endl;
	}

	if (isSorted(nonSortedArr, ARRAY_LEN))
        {
                cout << "Non-sorted array is sorted" << endl;
        }
        else
        {
                cout << "Non-sorted array is not sorted" << endl;
        }

	return 0;
}
