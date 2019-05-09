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

	Node();
	Node(std::string newName, int newId, double newLon, double newLan);
	int GetID();
	double GetX();
	double GetY();
	std::string GetName();
	Arc* HighestArc();
	Arc* LowestArc();
	std::vector<int> neighbors();
    bool isNeighbor(int arcID);
	void AddArc( Arc*);
	~Node();
};
