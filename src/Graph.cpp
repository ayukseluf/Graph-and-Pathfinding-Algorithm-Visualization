#include "Graph.h"

Graph::Graph(short nodeCount)
{
    this->nodeCount = nodeCount;

    // Generate nodes
    for (short i = 0; i < nodeCount; ++i)
        nodes.push_back(i);

    // Generate edges

}

void Graph::drawNodes() const
{
    for (Node n : nodes)
        n.Draw();
}

void Graph::Djikstra(short sourceNodeID)
{
    
}
