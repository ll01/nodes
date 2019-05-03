#include "Node.h"
#include "Arc.h"
class Node;
class Arc;
class Network
{
protected:
    std::map<int,Node*> m_nodeMap;
	std::map<std::string, Arc*> m_arcMap;
	void sync(const Network& input);
	
public:
    Network();
	Network(std::vector<Arc *> arcs, std::map<int, Node *> nodes);
    //Network(TravelType travelType);
	// void Generate(std::vector<Arc*>,std::map<int,Node*>);
	std::tuple<int, int, double> FindLongestArc();
	std::tuple<std::string , std::string, double> FindDistance(std::string x, std::string y);
	std::vector<int>  FindNeighbour(int);

	Node* FindNode(int);
	void addArc(Arc*);
	Arc* FindArc(std::string);
	void addNode(Node*);
	Network& operator+=(const Network& other);
	Network operator+( const Network& rhs);
	Network& operator=(const Network& rhs);
    ~Network();
};
class MainNetwork :public Network
{
private:
	/* data */
	std::map<TravelType,Network> m_subNetworks;
	void addToSubNetwork(TravelType,Arc*);
public:
	MainNetwork(/* args */);
	MainNetwork(std::vector<Arc *> arcs, std::map<int, Node *> nodes);
	std::vector<std::tuple<int, int, bool>> Check(TravelType travelType, std::vector<int> nodes);
	
	~MainNetwork();
};

