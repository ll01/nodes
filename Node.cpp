#include "Node.h"
#pragma once





Node::Node()
{
}

Node::Node(std::string newName, int newId, double newLon, double newLat)
{
	m_name = newName;
	m_id = newId;
	m_x = newLon;
	m_y = newLat;
}
int Node::GetID() {
	return m_id;
}

double Node::GetX() {
	return m_x;
}

double Node::GetY() {
	return m_y;
}

std::string Node::GetName()
{
	return m_name;
}

void Node::AddArc(Arc* arc) {
	m_arcs.push_back(arc);
}
Arc* Node::HighestArc() {
	double output = 0;
	Arc* connectingArc  = NULL;
	for(auto&& arc : m_arcs)
	{
		if(output < arc->GetLength()) {
			output = arc->GetLength();
			connectingArc  = arc;
		}
	}
	return connectingArc;
	
}

std::vector<int> Node::neighbors() {
	auto output = std::vector<int>();
	for(auto&& arc : m_arcs)
	{
		output.push_back(arc->GetNode(this)->m_id);
	}
	return output;
}

Node::~Node()
{
}
