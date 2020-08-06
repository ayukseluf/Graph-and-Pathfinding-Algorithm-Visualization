#pragma once

#include <vector>
#include "Edge.h"

class Path
{
    private:
        unsigned int sourceNodeID;
        std::vector<Edge> edgesToDestination;

    public:
        Path(unsigned int sourceNodeID, std::vector<Edge> &edgesToDestination);
};