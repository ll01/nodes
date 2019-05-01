#pragma once
#include "Node.h"
class Node;
enum TravelType
{
	rail = -1,
	ship = 1,
	bus = 2,
	bike = 3,
	foot = 4
};

class Arc
{
private:
	TravelType m_travel;
	Node* m_from;
	Node* m_to;
	double m_length;
	void calculateDistance();
public:
	static std::map<int, Arc*> allArcs;
	Arc();
	Arc(int from, int to, std::string travelType);
	double getLength();
	Node* GetNode(Node* from);
	~Arc();
};

