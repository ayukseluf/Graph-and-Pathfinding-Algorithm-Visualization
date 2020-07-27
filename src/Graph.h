#pragma once

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
        Graph(short nodeCount);
        void drawNodes() const;
        void Djikstra(short sourceNodeID);
};