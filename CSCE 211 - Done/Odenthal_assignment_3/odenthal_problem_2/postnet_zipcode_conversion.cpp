// Written by Quinton Odenthal

#include <iostream>
#include "postnet.h"

using namespace std;

int main()
{
	Postnet postnetCode("110100101000101011000010011");
	cout << "110100101000101011000010011" << endl;
	cout << postnetCode.getPostnet() << endl;
	cout << postnetCode.getZip() << endl;

	return 0;
}