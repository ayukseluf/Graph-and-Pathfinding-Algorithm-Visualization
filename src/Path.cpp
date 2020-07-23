#include "Path.h"

Path::Path(short sourceNodeID, std::vector<Edge> &edgesToDestination)
{
    this->sourceNodeID = sourceNodeID;
    this->edgesToDestination = edgesToDestination;
}