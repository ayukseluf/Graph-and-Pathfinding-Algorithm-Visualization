#pragma once

class Edge
{
    private:
        unsigned int int fromID, toID;
        short weight, edgeID;
    
    public:
        // Constructor
        Edge(unsigned int fromID, unsigned int toID, short weight, short edgeID);

        // Accessors
        short getEdgeID() const;
        short getFrom() const;
        short getTo() const;
        short getWeight() const;
};