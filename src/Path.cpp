#include "Path.h"

Path::Path(unsigned int sourceNodeID, std::vector<Edge> &edgesToDestination)
{
    this->sourceNodeID = sourceNodeID;
    this->edgesToDestination = edgesToDestination;
}