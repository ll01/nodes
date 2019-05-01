#include "Network.h"

Network::Network(std::vector<Arc *> allArcs, std::vector<Node *> allNodes)
{
}

std::string Network::FindLongestArc()
{
    auto allNodes = m_nodeMap;
    double longestArc = 0;
    Arc *obj = NULL;
    for (int i = 0; i < allNodes.size(); i++)
    {
        auto current = allNodes.at(i);
        auto checkedNodes = current->neighbors();

        for (int i = 0; i < checkedNodes.size(); i++)
        {
            allNodes.erase(checkedNodes.at(i));
        }
        if (longestArc < current->HighestArc()->getLength())
        {
            longestArc = current->HighestArc()->getLength();
            obj = current->HighestArc();
        }
    }
     return "";
}
