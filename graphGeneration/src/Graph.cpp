#include "Graph.h"

Graph::Graph(std::string fileName)
{
    this->nodeCount = 1000; // Needs to be manually updated for each following data set generation
    std::ifstream file(fileName);
    if (file.is_open()) {
        // cout << "In File" << endl;
        std::string row = "";
        while (getline(file, row)) {
            stringstream edgeData(row);
            std::string nodeID, X, Y;
            getline(edgeData, nodeID, ' ');
            unsigned int fromID = stof(nodeID);
            getline(edgeData, X, ' ');
            float xVar = stof(X);
            getline(edgeData, Y, ' ');
            float yVar = stof(Y);
            nodes.push_back(Node(fromID, xVar, yVar));
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

void Graph::Djikstra(Node node)
{
    
}
