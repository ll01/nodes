#include "Node.h"
#include "Arc.h"
class Node;
class Arc;
class Network
{
private:
  
    std::map<int,Node*> m_nodeMap;
	std::map<std::string, Arc*> m_arcMap;


	std::map<TravelType, Network*> subNetworks;
	void addSubNetwork(TravelType);
	void addArc(Arc*);
	void addNode(Node*);
public:
	static Network MainNetwork;
    Network();
    //Network(TravelType travelType);
	static void Generate(std::vector<Arc*>,std::map<int,Node*>);
    std::string FindLongestArc();
	Node* FindNode(int);
    ~Network();
};

