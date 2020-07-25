#pragma once
#include "ofMain.h"
#include <string>

/* Temporary */

class Node
{
	float x = ofRandom(5, 1915);
	float y = ofRandom(5, 1075);

public:
	string id = "temp";
	void draw() const;
};



