#pragma once

#include <fstream>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <queue>
#include "Edge.h"
#include "Node.h"

class Graph
{
    private:
        unsigned int nodeCount;
        unsigned int lastSourceNodeID; // ID of the source node most recently passed to Dijkstra
        std::vector<Node> nodes; // Indexed by ID
        std::vector<Edge> edgesInGraph; // Index by ID
        std::vector<int> predecessorNodesID;
        std::vector<float> distances;
      
    public:

        // Constructor
        Graph(unsigned int nodeCount, string fileName);

        // Accessors
        unsigned int getSelectedNodeID(float x, float y) const;
        std::pair<float,float> getCordsFromID(unsigned int nodeID) const;
        unsigned int getLastSourceNodeID() const;

        // Helper Functions
        void drawNodes() const;
        void drawEdges() const;
        void Dijkstra(unsigned int sourceID);
        std::stack<Edge> establishPath(unsigned int finalID);
};