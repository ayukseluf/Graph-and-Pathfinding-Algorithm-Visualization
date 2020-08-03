#pragma once

#include <vector>
#include "Edge.h"
#include "ofMain.h"

class Node
{
	std::vector< pair< unsigned int, float > > adjacentNodes; // <toID, weight>
	std::vector< Edge > adjacentEdges;
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
	std::vector<Edge> getAdjacentEdges() const;

	//Mutators
	void setAdjacentNodes(unsigned int toID, float weight);
	void setAdjacentEdges(Edge edge);

	// Helper Functions
	void Draw() const;
	bool isAdjacent(unsigned int toID) const;
};