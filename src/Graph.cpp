#include "Graph.h"

Graph::Graph(short nodeCount)
{
    this->nodeCount = nodeCount;

    // Generate nodes
    for (short i = 0; i < nodeCount; ++i)
        nodes.push_back(Node(i));

    // Generate edges - make sure to update the vector of edges for each node as well as push into edges vector for graph class

}

void Graph::drawNodes() const
{
    for (Node n : nodes)
        n.Draw();
}

void Graph::Djikstra(Node node)
{
    
}
