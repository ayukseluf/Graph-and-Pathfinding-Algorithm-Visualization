#pragma once

class Edge
{
    private:
        short fromID, toID, weight, edgeID;
    
    public:
        // Constructor
        Edge(short fromID, short toID, short weight, short edgeID);

        // Accessors
        short getEdgeID() const;
        short getFrom() const;
        short getTo() const;
        short getWeight() const;
};