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
	int m_id = -1;
	double m_x = 0;
	double m_y =0;
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
