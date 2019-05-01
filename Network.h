#include "Node.h"
#include "Arc.h"
class Node;
class Arc;
class Network
{
private:
    std::vector<Node*> m_nodes;
    std::map<int,Node*> m_nodeMap;
public:
    Network();
    Network(TravelType travelType);
    Network(std::vector<Arc*> , std::vector<Node*>);
    std::string FindLongestArc();
    ~Network();
};

Network::Network()
{
}

Network::~Network()
{
}
