#pragma once

#include <vector>
#include "Edge.h"

class Path
{
    private:
        short sourceNodeID;
        std::vector<Edge> edgesToDestination;

    public:
        Path(short sourceNodeID, std::vector<Edge> &edgesToDestination);
};