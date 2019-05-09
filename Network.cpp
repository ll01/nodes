#include "Network.h"
#include <iostream>

void Network::sync(const Network &input)
{
	for (auto const &arc : input.m_arcMap)
	{
		m_arcMap[arc.first] = arc.second;
	}

	for (auto const &node : input.m_nodeMap)
	{
		m_nodeMap[node.first] = node.second;
	}
}

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

Arc *Network::FindArc(std::string id)
{
	auto data = m_arcMap.find(id);
	Arc* found = nullptr;
	if (data != m_arcMap.end())
	{
		found = data->second;
	} 
	return found;
}

Arc *Network::FindArc(int one, int two) {
    auto arc = FindArc(std::to_string(one) + std::to_string(two));
    if (arc == nullptr) {
         arc = FindArc(std::to_string(two) + std::to_string(one));
    }
    return  arc;
}

void Network::addNode(Node *node)
{
	m_nodeMap[node->GetID()] = node;
}
Network &Network::operator+=(const Network &other)
{
	sync(other);
	return *this;
}
Network Network::operator+(const Network &rhs)
{
	auto network = Network();
	network.sync(*this);
	network.sync(rhs);
	return network;
}

std::tuple<int, int, double> Network::FindLongestArc()
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
	if (obj != nullptr)
	{
		Node *a;
		Node *b;
		std::tie(a, b) = obj->GetNodes();

		return std::make_tuple(a->GetID(), b->GetID(), longestArc);
	}
	return std::make_tuple(-1, -1, -1.0);
}

std::tuple<std::string, std::string, double> Network::FindDistance(std::string x, std::string y)
{
    auto arc = FindArc(x + y);
	if (arc != nullptr)
	{
		Node *a;
		Node *b;
		std::tie(a, b) = arc->GetNodes();
		return std::make_tuple(a->GetName(), b->GetName(), arc->GetLength());
	}
	return std::make_tuple("", "", -1);
}

std::vector<int> Network::FindNeighbour(int NodeId)
{
	auto node = m_nodeMap[NodeId];
	if (node != nullptr)
	{
		return node->neighbors();
	}
	return std::vector<int>();
}

std::vector<std::tuple<std::string, int, int>> genid(std::vector<int> nodeids)
{
	std::vector<std::tuple<std::string, int, int>> output;
	for (int i = 0; i < nodeids.size(); i++)
	{
		if (nodeids.at(i) != nodeids.back())
		{
			int current = nodeids.at(i);
			int next = nodeids.at(i + 1);
			std::string id = std::to_string(current) + std::to_string(next);
			auto data = std::make_tuple(id, current, next);
			output.push_back(data);
		}
	}
	return output;
}

std::vector<std::tuple<int, int, bool>> MainNetwork::Check(TravelType travelType, std::vector<int> nodes)
{
	std::vector<std::tuple<int, int, bool>> output;
	auto net = m_subNetworks[travelType];
	auto arcIDs = genid(nodes);
	for (auto const &idTuple : arcIDs)
	{
		std::string id;
		int to;
		int from;
		std::tie(id, to, from) = idTuple;
		bool exists = false;
		if (net.FindArc(id) != nullptr)
		{
			exists = true;
		}
		output.push_back(std::make_tuple(to, from, exists));
		if (exists == false)
		{
			break;
		}
	}
	return output;
}

Node *Network::FindNode(int id)
{
	auto data = m_nodeMap.find(id);
	if (data == m_nodeMap.end())
	{
		data->second = nullptr;
	}

	return data->second;
}
std::tuple<Arc*,int> findSmallest(std::vector<Arc*> arcs) {
	double smallest  = std::numeric_limits<double>::max();
	int index = 0;
	Arc* output = nullptr;
	for (int i = 0; i < arcs.size(); i++)
	{
		auto arc = arcs[i];
		if(smallest >= arc->GetLength()) {
			smallest = arc->GetLength();
			output = arc;
			index = i;
		}
	}
	return std::make_tuple( output,index);
}

int minDistance(std::map<int,double> distance, std::map<int,bool> spset) {
    int min =std::numeric_limits<double>::max();
    int index = distance.begin()->first;
    for (auto const &node : distance) {
          if (spset[node.first] == false && node.second <= min){
              min = node.second;
              index = node.first;
    }
     
    }
    return index;
}

std::map<int,double> Network::Dijkstra(int sourceID ,int destinationID ) {
    std::map<int,double>distance;
    std::map<int, std::vector<int>> visited;
    std::map<int,bool> spset;
    
    for (auto const &node : m_nodeMap) {
        spset[node.first] = false;
        distance[node.first] = std::numeric_limits<double>::max();
    }
    distance[sourceID] = 0;
    
    for (int i = 0; i < m_nodeMap.size() - 1; i++) {
        int u = 0;
        if (i == 0) {
            u = sourceID;
        } else {
            u  = minDistance( distance, spset);
            
        }
        spset[u]= true;
        for (auto const &node : m_nodeMap) {
            auto shortArc = FindArc(u, node.first);
            if (!spset[node.first] && shortArc != nullptr && distance[u] != std::numeric_limits<int>::max()) {
                
                if (distance[u]+ shortArc->GetLength() < distance[node.first]) {
                    distance[node.first] = distance[u]+ shortArc->GetLength();
                    visited[node.first].push_back(u);
                }
            }
        }
        
    }
    return  distance;
}

Network &Network::operator=(const Network &rhs)
{
	// TODO: insert return statement here
	if (&rhs != this)
	{
		m_arcMap = std::map<std::string, Arc *>(rhs.m_arcMap);
		m_nodeMap = std::map<int, Node *>(rhs.m_nodeMap);
		return *this;
	}
    return *this;
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
	for (auto const &arc : arcs)
	{
		addToSubNetwork(arc->GetTravelType(), arc);
	}
	m_subNetworks[bus] += m_subNetworks[rail];
	m_subNetworks[car] += m_subNetworks[bus] + m_subNetworks[ship];
	m_subNetworks[bike] += m_subNetworks[car];
	m_subNetworks[foot] += m_subNetworks[bike] + m_subNetworks[rail];
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

std::map<int,double>  MainNetwork::Dijkstra(TravelType travel, int sourceID, int destinationID) {
    return m_subNetworks[travel].Dijkstra(sourceID, destinationID);
}
MainNetwork::~MainNetwork()
{
}
