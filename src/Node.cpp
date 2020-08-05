#include "Node.h"

// --------------------------- Constructor ------------------------------

Node::Node(unsigned int ID, float x, float y)
{
	this->ID = ID;
	this->y = y;
	this->x = x;
}

// ---------------------------- Accessors -------------------------------

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

// ---------------------------- Mutators -------------------------------

void Node::setAdjacentNodes(unsigned int toID, float weight) 
{
	adjacentNodes.push_back(make_pair(toID, weight));
}

void Node::setAdjacentEdges(Edge edge) {
	adjacentEdges.push_back(edge);
}

// ------------------------ Helper Functions ---------------------------

void Node::Draw() const
{
	ofDrawCircle(x, y, 3);
}

// Returns true if toID is in this->adjacentNodes
bool Node::isAdjacent(unsigned int toID) const
{
	for (pair<unsigned int, float> p : adjacentNodes)
	{
		if (p.first == toID)
			return true;
	}
	return false;
}