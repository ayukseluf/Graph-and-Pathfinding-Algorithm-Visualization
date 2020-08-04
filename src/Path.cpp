#include "Path.h"

Path::Path(unsigned int sourceNodeID, unsigned int finalNodeID, std::stack<Edge> edgesToDestination)
{
    this->sourceNodeID = sourceNodeID;
    this->finalNodeID = finalNodeID;
    this->edgesToDestination = edgesToDestination;
}

stack<Edge> Path::getEdgesToDestination() const
{
    return edgesToDestination;
}