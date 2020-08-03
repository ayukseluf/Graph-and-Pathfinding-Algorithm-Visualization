#include "Graph.h"
#include <fstream>
#include <sstream>

Graph::Graph(unsigned int nodeCount, string fileName)
{
    this->nodeCount = nodeCount;
    load(fileName);
}
 
void Graph::load(string fileName)
{
    // Read data and build nodes
    std::ifstream file(fileName);
    string line = "";
    while (getline(file, line))
    {
        // Load source node's ID and coordinates
        stringstream edgeData(line);
        string sourceID = "";
        getline(edgeData, sourceID, ' ');
        string sourceX = "";
        getline(edgeData, sourceX, ' ');
        string sourceY = "";
        getline(edgeData, sourceY, ' ');
        
        // Construct source node
        nodes.push_back(Node(stoi(sourceID), stof(sourceX), stof(sourceY)));
        
        // Load source node's adjacency list
        string targetID = "";
        string targetWeight = "";
        while (getline(edgeData, targetID, ' '))
        {
            getline(edgeData, targetWeight, ' ');
            nodes[nodes.size() - 1].setAdjacentNodes(stoi(targetID), stof(targetWeight));
        }
    }
   
    // Build edges
    short nextEdgeID = 0;
    for (Node from : nodes)
    {
        for (pair< unsigned int, float > to : from.getAdjacentNodes())
        {
            edgesInGraph.push_back(Edge(from.getNodeID(), to.first, to.second, nextEdgeID)); // Edge(fromID, toID, weight, edgeID)
            nextEdgeID++;
        }
    }

    // Verify graph is undirected by ensuring that each source node is in each of it's target nodes adjacentNodes list
    // TODO

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

void Graph::drawEdges() const
{
    for (Edge e : edgesInGraph)
        ofDrawLine(getCordsFromID(e.getFrom()).first, getCordsFromID(e.getFrom()).second, getCordsFromID(e.getTo()).first, getCordsFromID(e.getTo()).second);
}

void Graph::Djikstra(Node node)
{
    
}
