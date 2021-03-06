#pragma once

#include <vector>
#include "ofMain.h"

class Node
{
	std::vector< pair< unsigned int, short > > adjacentNodes;
	unsigned int ID;
	float x, y;

public:

	// Constructor
	Node(unsigned int ID); // Delete !!
	Node(unsigned int ID, float x, float y);

	// Accessors
	unsigned int getNodeID() const;
	float getX() const;
	float getY() const;
	std::vector< pair< unsigned int, short > > getAdjacentNodes() const;

	// Helper Functions
	void Draw() const;
};



