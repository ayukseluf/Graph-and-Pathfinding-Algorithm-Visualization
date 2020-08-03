#pragma once

#include <vector>
#include "ofMain.h"

class Node
{
	std::vector< pair< unsigned int, float > > adjacentNodes; // <toID, weight>
	unsigned int ID;
	float x, y;

public:

	// Constructor
	Node(unsigned int ID, float x, float y);

	// Accessors
	unsigned int getNodeID() const;
	float getX() const;
	float getY() const;
	std::vector< pair< unsigned int, float > > getAdjacentNodes() const;

	//Mutators
	void setAdjacentNodes(unsigned int toID, float weight);

	// Helper Functions
	void Draw() const;
	bool isAdjacent(unsigned int toID) const;
};