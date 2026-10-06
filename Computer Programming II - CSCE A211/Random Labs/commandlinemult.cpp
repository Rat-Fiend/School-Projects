// Entire code written by Quinton Odenthal

#include <iostream>
#include <cstdlib>
using namespace std;
int main(int argc, char* argv[])
{
	int n = 1;

	for (int i = 1; i < argc; i++)
	{
		n = n * atoi(argv[i]);
	}

	cout << n << endl;

	return 0;
}

