#include "Node.h"

Node::Node(unsigned int ID, float x, float y)
{
	this->ID = ID;
	this->y = y;
	this->x = x;
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

void Node::setAdjacentNodes(unsigned int toID, short weight) {
	adjacentNodes.push_back(make_pair(toID, weight));
}

void Node::Draw() const
{
	ofDrawCircle(x, y, 3);
}
