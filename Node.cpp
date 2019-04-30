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
	m_lon = newLon;
	m_lat = newLat;
	Node::allNodes[m_id] = this;
}

Node::~Node()
{
}
