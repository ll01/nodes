#pragma once
#include <vector>
#include <string>
#include "Arc.h"
class Arc;
class Node
{
private:
	std::string m_name;
	int m_id;
	float lon;
	float lat;
	std::vector<Arc*>m_arcs;
public:
	Node();
	Node(std::string newName, int newId, float newLon, float newLan);
	//AddArc();
	~Node();
};

