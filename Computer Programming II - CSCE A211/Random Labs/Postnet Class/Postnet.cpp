#include "postnet.h"

using namespace std;

Postnet::Postnet(int zipEntry) : zipcode(zipEntry) {}

int Postnet::postnet_to_zip(string bitEntry)
{
	int zip = 0;

	for (int i = 1; i < bitEntry.length() - 2; i=i+5) // Iterate through the inner 25 characters of bitEntry, ignoring the outer 2 characters
	{
		int temp = 0;
		for (int j = 0; j < 5; j++) // Iterate through every group of 5 characters
		{
			switch (j)
			{
			case 0:
				temp += (bitEntry[j + i] - '0') * 7;
				break;
			case 1:
				temp += (bitEntry[j + i] - '0') * 4;
				break;
			case 2:
				temp += (bitEntry[j + i] - '0') * 2;
				break;
			case 3:
				temp += (bitEntry[j + i] - '0') * 1;
				break;
			case 4:
				temp += (bitEntry[j + i] - '0') * 0;
				break;
			}
		}

		if (temp == 11)
			temp = 0;

		switch (i)
		{
		case 1: // First 5 characters of bitEntry
			zip += temp * 10000; // First num of zip
			break;
		case 6: // Second 5 characters of bitEntry
			zip += temp * 1000; // Second num of zip
			break;
		case 11: // Third 5 characters of bitEntry
			zip += temp * 100; // Third num of zip
			break;
		case 16: // Fourth 5 characters of bitEntry
			zip += temp * 10; // Fourth num of zip
			break;
		case 21: // Final 5 characters of bitEntry
			zip += temp; // Final num of zip
			break;
		}
	}
	return zip;
}

string Postnet::zip_to_postnet(int zipEntry)
{
	string postnetCode = ""; // Initializing empty string

	postnetCode += '1'; // Add a 1 to the beginning of the string

	for (int i = 10000; i > 0; i = i / 10)
	{
		int temp = zipEntry / i; // Removes numbers to the right of the desired number
		temp = temp % 10; // Removes numbers to the left of the desired number

		switch (temp)
		{
		case 9:
			postnetCode = postnetCode + "10100";
			break;
		case 8:
			postnetCode = postnetCode + "10010";
			break;
		case 7:
			postnetCode = postnetCode + "10001";
			break;
		case 6:
			postnetCode = postnetCode + "01100";
			break;
		case 5:
			postnetCode = postnetCode + "01010";
			break;
		case 4:
			postnetCode = postnetCode + "01001";
			break;
		case 3:
			postnetCode = postnetCode + "00110";
			break;
		case 2:
			postnetCode = postnetCode + "00101";
			break;
		case 1:
			postnetCode = postnetCode + "00011";
			break;
		case 0:
			postnetCode = postnetCode + "11000";
			break;
		}
	}
	
	postnetCode += '1'; // Add a 1 to the end of the string

	return postnetCode;
}

Postnet::Postnet(string postnetEntry)
{
	zipcode = postnet_to_zip(postnetEntry);
}

int Postnet::getZip()
{
	return zipcode;
}

string Postnet::getPostnet()
{
	return zip_to_postnet(zipcode);
}