#include "Node.h"

Node::Node(unsigned int ID)
{
	this->ID = ID;
	x = ofRandom(5, ofGetWidth() - 5);
	y = ofRandom(5, ofGetHeight() - 5);
}

Node::Node(unsigned int ID, float x, float y)
{
	this->ID = ID;
	this->x = x;
	this->y = y;
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
