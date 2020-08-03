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
vector<Edge> Node::getAdjacentEdges() const {
	return this->adjacentEdges;
}
std::vector< pair<unsigned int, float> > Node::getAdjacentNodes() const
{
	return this->adjacentNodes;
}

void Node::setAdjacentNodes(unsigned int toID, float weight) 
{
	adjacentNodes.push_back(make_pair(toID, weight));
}

void Node::setAdjacentEdges(Edge edge) {
	adjacentEdges.push_back(edge);
}

void Node::Draw() const
{
	ofDrawCircle(x, y, 3);
}

// Returns true if toID is in adjacentNodes
bool Node::isAdjacent(unsigned int toID) const
{
	for (pair<unsigned int, float> p : adjacentNodes)
	{
		if (p.first == toID)
			return true;
	}
	return false;
}