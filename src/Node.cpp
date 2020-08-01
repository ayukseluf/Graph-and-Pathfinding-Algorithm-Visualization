#include "Node.h"

Node::Node(unsigned int ID)
{
	this->ID = ID;
	x = ofRandom(5, ofGetWidth() - 5);
	y = ofRandom(5, ofGetHeight() - 5);
}

unsigned int Node::getNodeID() const
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

std::vector< pair<unsigned int, short> > Node::getAdjacentNodes() const
{
	return this->adjacentNodes;
}

void Node::Draw() const
{
	ofDrawCircle(x, y, 3);
}
