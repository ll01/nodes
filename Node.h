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
	double m_lon;
	double m_lat;
	std::vector<Arc*>m_arcs;
public:
	static std::map<int, Node*> allNodes;
	Node();
	Node(std::string newName, int newId, double newLon, double newLan);
	//AddArc();
	~Node();
};

