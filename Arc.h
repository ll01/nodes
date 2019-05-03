#pragma once
#include "Node.h"
#include <map>
class Node;
enum TravelType
{
	rail = -1,
	ship = 1,
	car = 0,
	bus = 2,
	bike = 3,
	foot = 4
};

class Arc
{
private:
	TravelType m_travel;
	Node* m_from = NULL;
	Node* m_to = NULL;
	double m_length = 0;
	std::string m_id = ""; 
	void calculateDistance();
public:
	static std::map<int, Arc*> allArcs;
	Arc();
	Arc(int from, int to, TravelType travel, std::map<int ,Node*>);
	double GetLength();
	std::string GetID();
	TravelType GetTravelType();
	Node* GetNode(Node* from);
	std::tuple<Node*,Node*> GetNodes();

	~Arc();
};

