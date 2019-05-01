#include "Arc.h"
#include <cmath>
#include "Network.h"

std::map<int, Arc *> Arc::allArcs;
Arc::Arc()
{
}

Arc::Arc(int from, int to, std::string travelType, std::map<int,Node*> nodes)
{
	m_to = nodes[to];
	m_to->AddArc(this);
	m_from = nodes[from];
	m_from->AddArc(this);
	m_id = std::to_string(to) + std::to_string(from);
	calculateDistance();
}

double Arc::GetLength()
{
	return m_length;
}

std::string Arc::GetID()
{
	return m_id;
}

TravelType Arc::GetTravelType()
{
	return m_travel;
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
