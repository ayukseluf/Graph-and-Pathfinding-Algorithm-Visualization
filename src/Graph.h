#pragma once

#include <utility>
#include <vector>
#include "Edge.h"
#include "Path.h"
#include "Node.h"

class Graph
{
    private:
        short nodeCount;
        std::vector<Node> nodes; // Nodes indexed by ID
        std::vector<Edge> edgesInGraph; // Initialized in graph generation
        std::vector<Path> paths; // EMPTY until Djikstra called

    public:
        // Constructor
        Graph(short nodeCount);

        // Accessors
        short getSelectedNodeID(float x, float y) const;
        std::pair<float,float> getCordsFromID(short nodeID) const;

        // Helper Functions
        void drawNodes() const;
        void Djikstra(Node node);
};