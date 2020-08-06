#pragma once

#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include "Edge.h"
#include "Path.h"
#include "Node.h"

class Graph
{
    public:
        unsigned int nodeCount;
        std::vector<Node> nodes; // Nodes indexed by ID
        std::vector<Edge> edgesInGraph; // Initialized in graph generation
        std::vector<Path> paths; // EMPTY until Djikstra called
        // Constructor
        Graph(std::string fileName);

        // Accessors
        unsigned int getSelectedNodeID(float x, float y) const;
        std::pair<float,float> getCordsFromID(unsigned int nodeID) const;

        // Helper Functions
        void drawNodes() const;
        void Djikstra(Node node);
};