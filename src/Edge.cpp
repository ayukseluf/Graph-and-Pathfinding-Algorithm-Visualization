#include "Edge.h"

Edge::Edge(unsigned int from, unsigned int to, short weight, short ID)
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