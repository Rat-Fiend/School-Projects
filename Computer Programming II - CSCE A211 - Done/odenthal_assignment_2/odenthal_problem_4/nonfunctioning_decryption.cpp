// Authored by Quinton Odenthal
// This does not work

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void decrypt(int key, char origStr[]);
void decrypt(int key, char origStr[])
{
	int length = strlen(origStr);

	char decryptedStr[length + 1];

	strcpy(decryptedStr, origStr);
	int* temp = (int *) decryptedStr;

	for (int i=0; i<4; ++i) // I think this should be correct, but i only end up getting a bunch of gibberish
	{
		*(temp + i) = (int) *(temp + i) + key;
	}			// The two exclamation marks at the end of the origional phrase never change

	cout << decryptedStr;
}


int main()
{
	char origStr[] = ",vtaNm a_\"dabp!!";

	for (int i=1; i<=500; ++i)
	{
		cout << "Key: " << i << ", Phrase decrypted: ";
		decrypt(i, origStr);
		cout << endl;
	}

	return 0;
}
