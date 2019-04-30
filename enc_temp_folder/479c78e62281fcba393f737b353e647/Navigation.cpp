#include "Navigation.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <regex>
#include <fstream>
#include <boost/algorithm/string.hpp> 
using namespace std;

// Converts latitude/longitude into eastings/northings
extern void LLtoUTM(const double Lat, const double Long, double &UTMNorthing, double &UTMEasting);

Navigation::Navigation() : _outFile("Output.txt")
{
}

Navigation::~Navigation()
{
}

bool Navigation::ProcessCommand(const string& commandString)
{
	istringstream inString(commandString);
	string command;
	inString >> command;
	vector<string> commandParts;
	boost::split(commandParts, command, boost::is_any_of(","));

	// Add your code here

	return false;
}

bool Navigation::BuildNetwork(const string &fileNamePlaces, const string &fileNameLinks)
{
	fstream finPlaces(fileNamePlaces);
	fstream finLinks(fileNameLinks);
	if (finPlaces.fail() || finLinks.fail()) return false;
	std::string line;
	while (std::getline(finPlaces,line))
	{
		
		vector<std::string> data;
		boost::split(data, line, boost::is_any_of(","));
		std::cout << data[0] << std::endl;
		
	}

	return true;
}

// Add your code here
