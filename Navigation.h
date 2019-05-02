#pragma once

#include <fstream>
#include <string>

class Navigation
{
	std::ofstream _outFile;

	// Add your code here

public:
	Navigation();
	~Navigation();
	MainNetwork net;
	bool BuildNetwork(const std::string& fileNamePlaces, const std::string& fileNameLinks);
	bool ProcessCommand(const std::string& commandString);

	// Add your code here
};