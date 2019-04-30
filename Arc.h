#pragma once
#include "Node.h"
class Node;
enum TravelType
{

};

class Arc
{
private:
	TravelType m_travel;
	int m_from_id;
	int m_to_id;
public:
	static std::map<int, Arc*> allArcs;
	Arc();
	Arc(int from, int to, std::string travelType);
	~Arc();
};

