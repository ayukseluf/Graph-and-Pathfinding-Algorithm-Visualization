#pragma once
#include <stack>
#include <vector>
#include "Edge.h"


class Path
{
    private:
        //Either a stack or vector needs to go here
        std::stack<Edge> edgesToDestination;
        unsigned int sourceNodeID;
        unsigned int finalNodeID;

    public:
        
        //Constructor
        Path(unsigned int sourceNodeID, unsigned int finalNodeID, std::stack<Edge> edgesToDestination);

        //Accessors
        std::stack<Edge> getEdgesToDestination()const;
};