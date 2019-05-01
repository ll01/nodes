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
	// struct Node
	// {
	// 	/* data */
	// };
	
	static std::map<int, Node*> allNodes;
	Node();
	Node(std::string newName, int newId, double newLon, double newLan);
	int GetID();
	double GetX();
	double GetY();
	Arc* HighestArc();
	std::vector<int> neighbors();
	void AddArc( Arc*);
	~Node();
};
