#pragma once
#include "ofMain.h"

class Edge
{
    private:
        unsigned int fromID, toID;
        float weight;
        short edgeID;
    
    public:
        // Constructor
        Edge(unsigned int fromID, unsigned int toID, float weight, short edgeID);

        // Accessors
        short getEdgeID() const;
        short getFrom() const;
        short getTo() const;
        short getWeight() const;
};