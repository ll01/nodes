#pragma once
#include <vector>
#include <string>
#include "Arc.h"
#include <map>
class Arc;
class Node
{
private:
	std::string m_name;
	int m_id;
	double m_x;
	double m_y;
	std::vector<Arc*>m_arcs;
public:
	static std::map<int, Node*> allNodes;
	Node();
	Node(std::string newName, int newId, double newLon, double newLan);
	double GetX();
	double GetY();
	double HighestArc();
	void AddArc( Arc*);
	~Node();
};

