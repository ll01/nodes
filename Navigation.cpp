#include "Navigation.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <regex>
#include <fstream>
#include <boost/algorithm/string.hpp> 
#include "Node.h"
#include "Network.h"


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
	vector<std::string> data;
	map<int, Node*> nodes;
	while (std::getline(finPlaces,line))
	{
		boost::split(data, line, boost::is_any_of(","));
		auto id = std::atoi(data[1].c_str());
		double lon = std::atof(data[2].c_str());
		double lat = std::atof(data[3].c_str());
		auto node = new Node(data[0], id, lon, lat);
		nodes[id] = node;
	}
	vector<Arc*> arcs;
	while (std::getline(finLinks, line)) {
		boost::split(data, line, boost::is_any_of(","));
		auto from = std::atoi(data[0].c_str());
		auto to = std::atoi(data[1].c_str());
		auto link = new Arc(from, to, data[2], nodes);
		arcs.push_back(link);
	}
	Network::Generate(arcs, nodes);
	Network::MainNetwork.FindLongestArc();

	return true;
}

// Add your code here
	