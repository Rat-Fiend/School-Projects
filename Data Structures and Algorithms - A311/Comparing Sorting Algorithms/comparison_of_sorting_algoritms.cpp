/* Written by Quinton Odenthal */

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void printVector(vector<int>& arr, int n);
void insertionSort(vector<int>& arr, int n);
void mergeSort(vector<int>& arr, int const l, int const r);
void merge(vector<int>& arr, int const l, int const mid, int const r);
void quickSort(vector<int>& arr, int l, int r);
int partition(vector<int>& arr, int l, int r);

void printVector(vector<int>& arr, int n)
{
	for (int i = 0; i <= n - 1; i++)
	{
		cout << arr.at(i) << " ";
	}
	cout << endl;
}

void insertionSort(vector<int>& arr, int n)
{
	int temp = 0, j = 0;
	for (int i = 0; i < n - 1; i++)
	{
		j = i;
		while (j >= 0 && arr[j] > arr[j + 1])
		{
			temp = arr[j + 1];
			arr[j + 1] = arr[j];
			arr[j] = temp;
			j = j - 1;
		}
	}
}

void mergeSort(vector<int>& arr, int const l, int const r)
{
	if (l >= r)
		return; // Base case

	int mid = (r + l) / 2;
	mergeSort(arr, l, mid);
	mergeSort(arr, mid + 1, r);
	merge(arr, l, mid, r);
}

void merge(vector<int>& arr, int const l, int const mid, int const r)
{
	vector <int> mergedList;
	int left = l;
	int right = mid + 1;
	while ( (left <= mid) && (right <= r) )
	{
		if (arr[left] <= arr[right])
		{
			mergedList.push_back(arr[left]);
			left += 1;
		}
		else
		{
			mergedList.push_back(arr[right]);
			right += 1;
		}
	}
	while (left <= mid)
	{
		mergedList.push_back(arr[left]);
		left += 1;
	}
	while (right <= r)
	{
		mergedList.push_back(arr[right]);
		right += 1;
	}
	for (int i = 0; i < mergedList.size(); ++i)
	{
		arr[i + l] = mergedList[i];
	}
}

void quickSort(vector<int>& arr, int l, int r)
{
	if (l < r)
	{
		int pivot = partition(arr, l, r);

		quickSort(arr, l, pivot);
		quickSort(arr, pivot + 1, r);
	}
}

int partition(vector<int>& arr, int l, int r)
{
	int pivot = arr[l];
	int i = (l - 1);
	int j = (r + 1);

	while (true)
	{
		j--;
		while (arr[j] > pivot)
		{
			j--;
		}

		i++;
		while (arr[i] < pivot)
		{
			i++;
		}

		if (i < j)
		{
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
		{
			return j;
		}
	}
}

void fillVector(vector<int>& arr, const int SIZE)
{
	for (int i = 0; i <= SIZE - 1; ++i)
	{
		arr.push_back(rand() % (2 * SIZE));
	}
}

int main()
{
	srand(time(NULL));
	const int SIZE = 50000;
	int chooseSort = 0;

	vector <int> master;
	fillVector(master, SIZE);
	vector <int> test = master;


	auto start = high_resolution_clock::now(); // Start timepoint
	auto stop = high_resolution_clock::now(); // Ending timepoint
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Size of array to be sorted:" << SIZE << endl;
	for (int i = 0; i < 3; ++i)
	{
		chooseSort = i + 1;
		test = master;
		switch (chooseSort)
		{
		case 1:
			start = high_resolution_clock::now(); // Start timepoint
			insertionSort(test, SIZE);
			stop = high_resolution_clock::now(); // Ending timepoint
			cout << "Insertion sort used" << endl;
			break;
		case 2:
			start = high_resolution_clock::now(); // Start timepoint
			mergeSort(test, 0, SIZE - 1);
			stop = high_resolution_clock::now(); // Ending timepoint
			cout << "Merge sort used" << endl;
			break;
		case 3:
			start = high_resolution_clock::now(); // Start timepoint
			quickSort(test, 0, SIZE - 1);
			stop = high_resolution_clock::now(); // Ending timepoint
			cout << "Quick sort used" << endl;
			break;
		default:
			cout << "Invalid entry" << endl;
			break;
		}

		duration = duration_cast<microseconds>(stop - start);

		cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
	}

	return 0;
}