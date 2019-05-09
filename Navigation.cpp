#include "Navigation.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <regex>
#include <fstream> 
#include "Node.h"



using namespace std;

// Converts latitude/longitude into eastings/northings
extern void LLtoUTM(const double Lat, const double Long, double& UTMNorthing, double& UTMEasting);

Navigation::Navigation() : _outFile("Output.txt")
{
}

Navigation::~Navigation()
{
}
constexpr
unsigned int hash1(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (hash1(str, h + 1) * 33) ^ str[h];
}

TravelType convertToTravelType(const string & name ) {
    TravelType travel;
    switch (hash1(name.c_str()))
    {
        case hash1("Rail"):
            travel = rail;
            break;
        case hash1("Ship"):
            travel = ship;
            break;
        case hash1("Bus"):
            travel = bus;
            break;
        case hash1("Car"):
            travel = car;
            break;
        case hash1("Bike"):
            travel = bike;
            break;
        case hash1("Foot"):
            travel = foot;
            break;
    }
    return travel;
}
vector<string> split(const string & str, const string & delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}
bool Navigation::ProcessCommand(const string & commandString)
{
	bool state = false;

	vector<string> commandParts;
	commandParts = split(commandString, " ");
	auto action = commandParts[0].c_str();
	switch (hash1(action))
	{
	case hash1("MaxDist"):
		
		break;
	case hash1("MaxLink"):
	{
		int to = 0;
		int from = 0;
		double distance = 0.0;
		std::tie(to, from, distance) = c.FindLongestArc();
		if (distance > 0) {
			std::cout << to << "," << from << "," << std::setprecision(3) << distance << std::endl;
			state = true;
		}
	}
	break;
	case hash1("FindDist"): {
		string to;
		string from;
		double distance;
		std::tie(to, from, distance) = c.FindDistance(commandParts[2], commandParts[1]);
		if (distance > 0) {
			std::cout << to << "," << from << "," << std::setprecision(3) << distance << std::endl;
			state = true;
        } else {
            std::tie(to, from, distance) = c.FindDistance(commandParts[1], commandParts[2]);
            if (distance > 0) {
                std::cout << to << "," << from << "," << std::setprecision(3) << distance << std::endl;
                state = true;
            }
            
        }

	}
    break;
	case hash1("FindNeighbour"):
	{
		auto data = c.FindNeighbour(std::stoi(commandParts[1]));
		if (data.size() > 0) {
			for (auto const& x : data)
			{
				std::cout << x << std::endl;
			}
			std::cout << std::endl;
			state = true;
		}
	}
	break;
	case hash1("Check"):
	{
		  auto travel  = convertToTravelType(commandParts[1]);
		vector<int> nodes;
		for (int i = 2; i < commandParts.size(); i++)
		{
			nodes.push_back(std::stoi(commandParts.at(i)));
		}
      
		auto data = c.Check(travel, nodes);
		if (data.size() > 0) {
			for (auto const& line : data)
			{
				int x;
				int y;
				bool ok;
				std::tie(x, y, ok) = line;
				std::cout << x << "," << y << "," << std::boolalpha << ok << std::endl;
			}
			state = true;
		}
		
	}
		break;
	case hash1("FindRoute"):
        {
            auto travel = convertToTravelType(commandParts[1]);
            auto a = std::stoi(commandParts[2]);
            auto b = std::stoi(commandParts[3]);
            c.Dijkstra(travel,a,b);
        }
		break;
	case hash1("FindShortestRoute"):
		break;
	default:
		break;
	}
	

	// Add your code here

	return state;
}



bool Navigation::BuildNetwork(const string & fileNamePlaces, const string & fileNameLinks)
{
	fstream finPlaces(fileNamePlaces);
	fstream finLinks(fileNameLinks);
    if (finPlaces.fail() || finLinks.fail()) return false;
	std::string line;
	vector<std::string> data;
	map<int, Node*> nodes;
	while (std::getline(finPlaces, line))
	{
		data = split(line, ",");
		auto id = std::atoi(data[1].c_str());
		double lon = std::atof(data[2].c_str());
		double lat = std::atof(data[3].c_str());
		auto node = new Node(data[0], id, lon, lat);
		nodes[id] = node;
	}
	vector<Arc*> arcs;
	while (std::getline(finLinks, line)) {
		data = split(line, ",");
		auto to = std::atoi(data[0].c_str());
		auto from = std::atoi(data[1].c_str());
		TravelType travel = rail;
		switch (hash1(data[2].c_str()))
		{
		case hash1("Rail"):
			travel = rail;
			break;
		case hash1("Ship"):
			travel = ship;
			break;
		case hash1("Car"):
			travel = car;
			break;
		case hash1("Bus"):
			travel = bus;
			break;
		case hash1("Bike"):
			travel = bike;
			break;
		case hash1("Foot"):
			travel = foot;
			break;
		default:
			std::cout << ",,," << "\n";
			exit(1);
			break;
		}
		auto link = new Arc(to,from, travel, nodes);
		arcs.push_back(link);
	}
	c = MainNetwork(arcs, nodes);
	//Network::MainNetwork.FindLongestArc();

	return true;
}

// Add your code here
