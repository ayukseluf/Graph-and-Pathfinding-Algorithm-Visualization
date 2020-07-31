#include "Graph.h"

Graph::Graph(unsigned int nodeCount)
{
    this->nodeCount = nodeCount;

    // Generate nodes
    for (unsigned int i = 0; i < nodeCount; i++)
        nodes.push_back(Node(i));

    // Generate edges - make sure to update the vector of edges for each node as well as push into edges vector for graph class
    for(unsigned int i = 0; i < nodes.size(); i++)
    {

    }
}

// Returns ID of node at (x,y) or -1 if not found
unsigned int Graph::getSelectedNodeID(float x, float y) const
{
    for (Node n : nodes)
    {
        if (ofDist(x, y, n.getX(), n.getY()) <= 3)
            return n.getNodeID();
    }

    return -1;
}

std::pair<float, float> Graph::getCordsFromID(unsigned int nodeID) const
{
    return std::make_pair(nodes[nodeID].getX(), nodes[nodeID].getY());
}

void Graph::drawNodes() const
{
    for (Node n : nodes)
        n.Draw();
}

void Graph::Djikstra(Node node)
{
    
}
