#include "Node.h"
#include "Arc.h"
class Node;
class Arc;
class Network
{
protected:
    std::map<int,Node*> m_nodeMap;
	std::map<std::string, Arc*> m_arcMap;
	
public:
	static Network MainNetwork;
    Network();
	Network(std::vector<Arc *> arcs, std::map<int, Node *> nodes);
    //Network(TravelType travelType);
	// void Generate(std::vector<Arc*>,std::map<int,Node*>);
    std::string FindLongestArc();
	Node* FindNode(int);
	void addArc(Arc*);
	void addNode(Node*);
	Network& operator+(const Network& other);
	Network& operator=(const Network& other);
    ~Network();
};
class MainNetwork: private Network
{
private:
	/* data */
	std::map<TravelType,Network> m_subNetworks;
	void addToSubNetwork(TravelType,Arc*);
public:
	MainNetwork(/* args */);
	MainNetwork(std::vector<Arc *> arcs, std::map<int, Node *> nodes);
	void Generate(std::vector<Arc*>,std::map<int,Node*>);
	
	~MainNetwork();
};

