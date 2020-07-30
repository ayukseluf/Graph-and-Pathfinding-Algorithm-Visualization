#pragma once

#include <vector>
#include "ofMain.h"

class Node
{
	std::vector< pair< short, short > > adjacentNodes;
	short ID;
	float x, y;

public:

	// Constructor
	Node(short ID);

	// Accessors
	short getNodeID() const;
	float getX() const;
	float getY() const;
	std::vector< pair< short, short > > getAdjacentNodes() const;

	// Helper Functions
	void Draw() const;
};



