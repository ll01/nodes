#include "Node.h"
#include <algorithm>
#pragma once





Node::Node()
{
	m_name = "";
	m_id = -1;
	m_x = 0;
	m_y = 0;
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
	std::sort(m_arcs.begin(), m_arcs.end());
}
Arc* Node::HighestArc() {
	// double output = 0;
    Arc* connectingArc  = NULL;
	// for(auto&& arc : m_arcs)
	// {
	// 	if(output < arc->GetLength()) {
	// 		output = arc->GetLength();
	// 		connectingArc  = arc;
	// 	}
	// }
	// return connectingArc;
    if (m_arcs.size() > 0) {
        connectingArc = m_arcs.back();
    }
    return connectingArc;
}

Arc* Node::LowestArc() {
	return m_arcs.front();
}


std::vector<int> Node::neighbors() {
	auto output = std::vector<int>();
	for(auto&& arc : m_arcs)
	{
		output.push_back(arc->GetNode(this)->m_id);
	}
	return output;
}
bool Node::isNeighbor(int arcID){
    bool isNeibor = false;
    
    auto n = neighbors();
    if (arcID == m_id) {
        isNeibor = true;
    } else {
        isNeibor = std::find(n.begin(),n.end(), arcID) != n.end();
    }
    return isNeibor;
}
Node::~Node()
{
}
