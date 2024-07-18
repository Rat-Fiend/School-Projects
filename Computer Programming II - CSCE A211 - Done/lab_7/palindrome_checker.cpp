// Entire code written by Quinton Odenthal

#include <iostream>
#include <cstring>
using namespace std;

bool isPalindrome(char* p, int length);

int main()
{
	char* cstr = new char[15];
	char c = ' ';
	do
	{
		cout << "Enter a string less than 14 characters." << endl;
		cin >> cstr;
		int len = strlen(cstr); 
		cout << "You typed: " << cstr << ". ";
		cout << "It is " << len << " characters long." << endl;
		cout << "That string is ";
		if (!isPalindrome(cstr, len))
		{
			cout << "not ";
		}
		cout << "a palindrome." << endl;

		cout << "Enter 'y' to repeat." << endl;
		cin >> c;
	} while (c == 'y');
	delete[] cstr;
}

bool isPalindrome(char* p, int length)
{
	// Could only check half the length to save half the time, not done here though
	int j = length - 1;
	for (int i=0; i<length; ++i)
	{
		if (p[i] != p[j])
		{
			return false;
		}
		--j;
	}
	return true;
} 

