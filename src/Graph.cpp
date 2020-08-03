#include "Graph.h"
#include <fstream>
#include <sstream>

Graph::Graph(unsigned int nodeCount, string fileName)
{
    this->nodeCount = nodeCount;

    // Read file and build nodes
    std::ifstream file(fileName);
    string line = "";
    short nextEdgeID = 0;
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

        // Load source node's adjacency list annd construct edges
        string targetID = "";
        string targetWeight = "";
        while (getline(edgeData, targetID, ' '))
        {
            getline(edgeData, targetWeight, ' ');
            nodes[stoi(sourceID)].setAdjacentNodes(stoi(targetID), stof(targetWeight));
            edgesInGraph.push_back(Edge(stoi(sourceID), stoi(targetID), stof(targetWeight), nextEdgeID));
            nodes[stoi(sourceID)].setAdjacentEdges(edgesInGraph[nextEdgeID]);
            nextEdgeID++;
        }
    }

   // !!!NOTE: This code has a horrible complexity and if Dijkstras can be implemented without ensuring that nodes are reciprocally in adjacency lists then delete/
   // Ensures that the graph is undirected by making sure adjacent nodes are in each others adjaceny list
    for (Node from : nodes)
    {
        for (pair< unsigned int, float > to : from.getAdjacentNodes())
        {
            if (!nodes[to.first].isAdjacent(from.getNodeID()))
                nodes[to.first].setAdjacentNodes(from.getNodeID(), to.second);
        }
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

void Graph::drawEdges() const
{
    for (Edge e : edgesInGraph)
        ofDrawLine(getCordsFromID(e.getFrom()).first, getCordsFromID(e.getFrom()).second, getCordsFromID(e.getTo()).first, getCordsFromID(e.getTo()).second);
}

void Graph::Dijkstra(Node node)
{
    //visited will start empty and unvisited will be full
    vector <Node> visited;
    vector <Node> unvisited = nodes;

    //First Initialize distance vector to a max value, and vectors holding previous nodes and edges to -1
    for (unsigned int i = 0; i < nodes.size(); i++) {
        distances[i] = 1000000000;
        predecessorNodesID[i] = -1;
        predecessorEdgesID[i] = -1;
    }

    while (unvisited.begin() != unvisited.end()) {
    
    }
}