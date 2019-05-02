#include "Network.h"
#include <iostream>

Network Network::MainNetwork = Network();

Network::Network()
{
}

Network::Network(std::vector<Arc *> arcs, std::map<int, Node *> nodes)
{
	for (auto &&arc : arcs)
	{
		addArc(arc);
	}
	m_nodeMap = nodes;
}

void Network::addArc(Arc *arc)
{
	m_arcMap[arc->GetID()] = arc;
	//subNetworks[arc->GetTravelType]-> ;
}

void Network::addNode(Node *node)
{
	m_nodeMap[node->GetID()] = node;
}
std::string Network::FindLongestArc()
{
	auto allNodes = m_nodeMap;
	double longestArc = 0;
	Arc *obj = NULL;

	for (auto const &x : allNodes)
	{
		auto current = x.second;
		auto checkedNodes = current->neighbors();
		for (int i = 0; i < checkedNodes.size(); i++)
		{
			allNodes.erase(checkedNodes.at(i));
		}
		//std::cout << current->) << std::endl;
		auto a = current->HighestArc();
		if (a != NULL && longestArc < a->GetLength())
		{
			longestArc = current->HighestArc()->GetLength();
			obj = current->HighestArc();
		}
	}

	return "";
}

Node *Network::FindNode(int id)
{
	return m_nodeMap[id];
}

Network::~Network()
{
}

MainNetwork::MainNetwork()
{
}

MainNetwork::MainNetwork(std::vector<Arc *> arcs, std::map<int, Node *> nodes)
	: Network(arcs, nodes)
{
}
void MainNetwork::Generate(std::vector<Arc *> arcs, std::map<int, Node *> nodes)
{

	for (auto const &arc : arcs)
	{
		switch (arc->GetTravelType())
		{
		case rail:
			addToSubNetwork(arc->GetTravelType(), arc);
			break;
		case ship:
			addToSubNetwork(arc->GetTravelType(), arc);
			break;
		case bus:
			addToSubNetwork(arc->GetTravelType(), arc);
			break;
		case bike:
			addToSubNetwork(arc->GetTravelType(), arc);
			break;
		}
		m_subNetworks[arc->GetTravelType()].addArc(arc);
	}
	m_subNetworks[bus] += m_subNetworks[rail];
	m_subNetworks[bike] += m_subNetworks[bus];
	m_subNetworks[foot] = m_subNetworks[bike] + m_subNetworks[rail];
}
void MainNetwork::addToSubNetwork(TravelType travelType, Arc *arc)
{
	m_subNetworks[travelType].addArc(arc);
	Node *a;
	Node *b;
	std::tie(a, b) = arc->GetNodes();
	m_subNetworks[travelType].addNode(a);
	m_subNetworks[travelType].addNode(b);
}

MainNetwork::~MainNetwork()
{
}
