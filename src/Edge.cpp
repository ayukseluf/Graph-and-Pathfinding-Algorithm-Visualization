#include "Edge.h"

// --------------------------- Constructor ------------------------------

Edge::Edge(unsigned int fromID, unsigned int toID, float weight, short edgeID)
{
    this->fromID = fromID;
    this->toID = toID;
    this->weight = weight;
    this->edgeID = edgeID;
}

// ---------------------------- Accessors -------------------------------

unsigned int Edge::getFrom() const
{
    return this->fromID;
}

unsigned int Edge::getTo() const
{
    return this->toID;
}

float Edge::getWeight() const
{
    return this->weight;
}

short Edge::getEdgeID() const
{
    return this->edgeID;
}