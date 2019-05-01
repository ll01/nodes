#include "Arc.h"
#include <cmath>

std::map<int, Arc *> Arc::allArcs;
Arc::Arc()
{
}

Arc::Arc(int from, int to, std::string travelType)
{
	m_to = Node::allNodes[to];
	m_to->AddArc(this);
	m_from = Node::allNodes[from];
	m_from->AddArc(this);
	calculateDistance();
}
void Arc::calculateDistance()
{
	auto xDelta = m_to->GetX() - m_from->GetX();
	auto yDelta = m_to->GetY() - m_from->GetY();
	m_length = sqrt(pow(xDelta, 2) + pow(yDelta, 2));
}

Node *Arc::GetNode(Node *from)
{
	Node *node = NULL;
	if (m_from->GetID() != from->GetID())
	{
		node = m_from;
	}
	else
	{
		node = m_to;
	}
	return node;
}

Arc::~Arc()
{
}
