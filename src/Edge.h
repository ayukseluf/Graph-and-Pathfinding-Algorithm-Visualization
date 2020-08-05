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
        unsigned int getFrom() const;
        unsigned int getTo() const;
        float getWeight() const;
};