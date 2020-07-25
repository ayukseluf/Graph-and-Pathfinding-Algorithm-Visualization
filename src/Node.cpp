#include "Node.h"

void Node::draw() const
{
	ofFill();
	ofSetColor(3, 218, 198);
	ofDrawCircle(x, y, 2);
}
