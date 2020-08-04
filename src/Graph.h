#pragma once

#include <utility>
#include <vector>
#include "Edge.h"
#include "Path.h"
#include "Node.h"

using std::string;

class Graph
{
    private:
        unsigned int nodeCount;
        std::vector<Node> nodes; // Nodes indexed by ID
        std::vector<Edge> edgesInGraph; // Initialized in graph generation
        std::vector<int> predecessorNodesID;
        std::vector<float> distances;
      
    public:
        // Constructor
        Graph(unsigned int nodeCount, string fileName);

        // Accessors
        unsigned int getSelectedNodeID(float x, float y) const;
        std::pair<float,float> getCordsFromID(unsigned int nodeID) const;

        // Helper Functions
        void drawNodes() const;
        void drawEdges() const;
        void Dijkstra(unsigned int sourceID);
        Path establishPath(unsigned int sourceID, unsigned int finalID);
};