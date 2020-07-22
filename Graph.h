#pragma once

#include <vector>
#include "Edge.h"
#include "Path.h"

class Graph
{
    private:
        short nodeCount;
        std::vector<short> nodes;
        std::vector<Edge> edgesInGraph; // Initialized in graph generation
        std::vector<Path> paths; // EMPTY until Djikstra called

    public:
        Graph(short nodeCount);
        void Djikstra(short sourceNodeID);
};