#pragma once
#include <string>

using namespace std;

class Postnet
{
private:
	int zipcode;
public:
	Postnet(int zipEntry);
	Postnet(string bitEntry);

	int postnet_to_zip(string bitEntry);
	string zip_to_postnet(int zipEntry);

	int getZip();
	string getPostnet();
};