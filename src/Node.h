#pragma once

#include "ofMain.h"

class Node
{
	short ID;
	float x, y;

public:

	// Constructor
	Node(short ID);

	// Accessors
	short getNodeID() const;
	float getX() const;
	float getY() const;

	// 
	void Draw() const;
};



