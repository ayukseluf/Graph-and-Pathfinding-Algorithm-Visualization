#include "Node.h"

Node::Node(short ID)
{
	this->ID = ID;
	x = ofRandom(5, ofGetWidth() - 5);
	y = ofRandom(5, ofGetHeight() - 5);
}

short Node::getNodeID() const
{
	return ID;
}

float Node::getX() const
{
	return x;
}

float Node::getY() const
{
	return y;
}

std::vector< pair<short, short> > Node::getAdjacentNodes() const
{
	return this->adjacentNodes;
}

void Node::Draw() const
{
	ofFill();
	ofSetColor(3, 218, 198);
	ofDrawCircle(x, y, 2);
}
