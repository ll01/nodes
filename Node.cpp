#include "Node.h"
#pragma once




std::map<int, Node*> Node::allNodes;
Node::Node()
{
}

Node::Node(std::string newName, int newId, double newLon, double newLat)
{
	m_name = newName;
	m_id = newId;
	m_x = newLon;
	m_y = newLat;
	Node::allNodes[m_id] = this;
}
double Node::GetX() {
	return m_x;
}

double Node::GetY() {
	return m_y;
}

void Node::AddArc(Arc* arc) {
	m_arcs.push_back(arc);
}
double Node::HighestArc() {
	double output = 0;
	Arc* connectingArc  = NULL;
	for(auto&& arc : m_arcs)
	{
		if(output < arc->getLength()) {
			output = arc->getLength();
			connectingArc  = arc;
		}
	}
	return output;
	
}

Node::~Node()
{
}
