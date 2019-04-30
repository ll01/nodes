#pragma once
#include "Node.h"
class Node;
enum TravelType
{

};

class Arc
{
private:
	TravelType m_travel;
	Node* m_node;
public:
	Arc();
	~Arc();
};

