#include "Arc.h"

std::map<int, Arc*> Arc::allArcs;
Arc::Arc()
{
}

Arc::Arc(int from, int to, std::string travelType)
{
	m_from_id = from;
	m_from_id = to;
}


Arc::~Arc()
{
}
