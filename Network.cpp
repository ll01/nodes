#include "Network.h"
#include <iostream>

Network Network::MainNetwork = Network();

Network::Network()
{
}

void Network::Generate(std::vector<Arc*> arcs, std::map<int, Node*> nodes)
{
	for (auto&& arc : arcs)
	{
		Network::MainNetwork.addArc(arc);
	}
	Network::MainNetwork.m_nodeMap = nodes;
}

void Network::addSubNetwork(TravelType travel) {
	if (Network::MainNetwork.subNetworks[travel] == NULL) {
		Network::MainNetwork.subNetworks[travel] =new Network();
	}
	 
}
void Network::addArc(Arc* arc) {
	m_arcMap[arc->GetID()] = arc;
	//subNetworks[arc->GetTravelType]-> ;
}

void Network::addNode(Node* node) {;
	m_nodeMap[node->GetID()] = node; 
}
std::string Network::FindLongestArc()
{
    auto allNodes = m_nodeMap;
    double longestArc = 0;
    Arc *obj = NULL;


	for (auto const& x : allNodes)
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

Node* Network::FindNode(int id)
{
	return m_nodeMap[id];
}

Network::~Network()
{
}
