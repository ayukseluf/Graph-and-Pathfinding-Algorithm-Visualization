#include "Edge.h"

Edge::Edge(unsigned int fromID, unsigned int toID, float weight, short edgeID)
{
    this->fromID = fromID;
    this->toID = toID;
    this->weight = weight;
    this->edgeID = edgeID;
}

short Edge::getFrom() const
{
    return this->fromID;
}

short Edge::getTo() const
{
    return this->toID;
}

short Edge::getWeight() const
{
    return this->weight;
}

short Edge::getEdgeID() const
{
    return this->edgeID;
}