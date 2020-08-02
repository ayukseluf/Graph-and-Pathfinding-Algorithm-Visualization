#include "Graph.h"
#include <fstream>
#include <sstream>
Graph::Graph(unsigned int nodeCount, string fileName)
{
    this->nodeCount = nodeCount;

    // Generate nodes
    for (unsigned int i = 0; i < nodeCount; i++)
        nodes.push_back(Node(i));

    // Read Edges from file
    loadEdges(fileName);

}
void Graph::loadEdges(string fileName) {
    ifstream file(fileName);
    string row, fromIDString, toIDString, weightString;
    unsigned int fromID, toID;
    short weight;
    short edgeID = 0;
    cout << "In load function" << endl;
    if (file.is_open()) {
        cout << "In File" << endl;
        while (getline(file, row)) {
            stringstream edgeData(row);
            getline(edgeData, fromIDString, ' ');
            fromID = stoi(fromIDString);
            getline(edgeData, toIDString, ' ');
            toID = stoi(toIDString);
            getline(edgeData, weightString, ' ');
            weight = stoi(weightString);
            nodes[fromID].setAdjacentNodes(toID, weight);
            Edge edge(fromID, toID, weight, edgeID);
            edgesInGraph.push_back(edge);
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
