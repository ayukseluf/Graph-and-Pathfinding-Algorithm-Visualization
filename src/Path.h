#pragma once

#include <vector>
#include "Edge.h"
#include "Graph.h"

class Path
{
    private:
        //Either a stack or vector needs to go here
        unsigned int sourceNodeID;
        std::vector<Edge> edgesToDestination;

    public:
        Path(unsigned int sourceNodeID, std::vector<Edge> &edgesToDestination);
};