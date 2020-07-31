#include "ofApp.h"

void ofApp::setup()
{
	graph = nullptr;
	generateGraph(1000);
	
	// Intialization
	showAllMenus = true;
	showHelp = true;
	showSettings = true;
	showResults = true;

	// Styling // TODO: need to scale gui with window size
	ofBackground(80);
	guiElementWidth = 250; 
	guiElementHeight = 20;
	ofxGuiSetDefaultWidth(guiElementWidth);
	ofxGuiSetDefaultHeight(guiElementHeight);

	// Listeners
	targetNodeSlider.addListener(this, &ofApp::targetNodeSliderChanged);
	sourceNodeSlider.addListener(this, &ofApp::sourceNodeSliderChanged);
	selectedNodeSlider.addListener(this, &ofApp::selectedNodeSliderChanged);
	setSourceButton.addListener(this, &ofApp::setSourceButtonPressed);
	setTargetButton.addListener(this, &ofApp::setTargetButtonPressed);

	// Help Gui
	helpGui.setup("Help");
	helpGui.setPosition(ofGetWidth() - guiElementWidth - 5, 150);
	helpGui.add(keyBinding1.setup("Toggle All", "     tab"));
	helpGui.add(keyBinding2.setup("Toggle Help", "    h"));
	helpGui.add(keyBinding3.setup("Toggle Settings", "s"));
	helpGui.add(keyBinding4.setup("Toggle Results", " r"));
	helpGui.add(keyBinding5.setup("Selected Node", "left / right"));
	helpGui.add(keyBinding6.setup("Set Source Node", "up"));
	helpGui.add(keyBinding7.setup("Set Target Node", "down"));
	helpGui.add(keyBindingLast.setup("Quit","           esc"));

	// Settings Gui
	settingsGui.setup("Settings");
	settingsGui.setPosition(ofGetWidth() - guiElementWidth - 5, 370);
	settingsGui.add(totalNodesSlider.setup("Total Nodes", totalNodes, 10, 1000));
	settingsGui.add(stackOverflowNodesToggle.setup("100k Nodes", false));
	settingsGui.add(spacer1.setup("",""));
	settingsGui.add(sourceNodeSlider.setup("Source Node ID", sourceNodeID, 0, totalNodes - 1));
	settingsGui.add(highlightSourceToggle.setup("Highlight", false));
	settingsGui.add(targetNodeSlider.setup("Target Node ID", targetNodeID, 0, totalNodes - 1));
	settingsGui.add(highlightTargetToggle.setup("Highlight", false));
	settingsGui.add(spacer2.setup("", ""));
	settingsGui.add(selectedNodeSlider.setup("Selected Node", selectedNodeID, 0, totalNodes - 1));
	settingsGui.add(selectedCordLabel.setup("Coordinates", makeSelectedCordLabel()));
	settingsGui.add(highlightSelectedToggle.setup("Highlight", false));
	settingsGui.add(setSourceButton.setup("Set as Source"));
	settingsGui.add(setTargetButton.setup("Set as Target"));
	settingsGui.add(spacer3.setup("", ""));
	settingsGui.add(animationSpeedSlider.setup("Animation Speed", 1.0, .1, 10));
	settingsGui.add(velocitySlider.setup("Velocity", 20, .1, 100));
	settingsGui.add(timeLimitSlider.setup("Time Limit", 500, 1, 1000));

	// Results Gui
	resultsGui.setup("Results");
	resultsGui.setPosition(ofGetWidth() - guiElementWidth - 5, 770);
	resultsGui.add(idealTimeLabel.setup("Ideal Time Taken","   0:00"));
	resultsGui.add(actualTimeLabel.setup("Actual Time Taken","  0:00"));
	resultsGui.add(timeDeltaLabel.setup("Inefficiency Delta", " 0:00"));
}

void ofApp::update()
{

}

void ofApp::draw()
{
	graph->drawNodes();

	ofSetColor(0, 255, 0);
	if (highlightSourceToggle)
		drawArrow(graph->getCordsFromID(sourceNodeID), "From");
	ofSetColor(255, 0, 0);
	if (highlightTargetToggle)
		drawArrow(graph->getCordsFromID(targetNodeID), "To");
	ofSetColor(255, 255, 0);
	if (highlightSelectedToggle)
		drawArrow(graph->getCordsFromID(selectedNodeID), "Selected");

	if(showHelp)
		helpGui.draw();
	if(showSettings)
		settingsGui.draw(); 
	if(showResults)
		resultsGui.draw();
}

// ------------------------------ Listeners ------------------------------

void ofApp::sourceNodeSliderChanged(int& sourceNode)
{
	sourceNodeID = sourceNode;
}


void ofApp::targetNodeSliderChanged(int& targetNode)
{
	targetNodeID = targetNode;
}


void ofApp::selectedNodeSliderChanged(int& selectedNode)
{
	selectedNodeID = selectedNode;
	selectedCordLabel = makeSelectedCordLabel();
}


void ofApp::setSourceButtonPressed()
{
	sourceNodeSlider = selectedNodeID;
}


void ofApp::setTargetButtonPressed()
{
	targetNodeSlider = selectedNodeID;
}

// --------------------------- Helper Functions ---------------------------

void ofApp::generateGraph(unsigned int numNodes)
{
	delete graph;
	graph = new Graph(numNodes);
	
	totalNodes = numNodes;
	totalNodesSlider = totalNodes;

	sourceNodeSlider.setMax(totalNodes - 1);
	sourceNodeID = totalNodes / 4;
	sourceNodeSlider = sourceNodeID;

	targetNodeSlider.setMax(totalNodes - 1);
	targetNodeID = totalNodes / 4 * 3;
	targetNodeSlider = targetNodeID;
	
	selectedNodeSlider.setMax(totalNodes - 1);
	selectedNodeID = totalNodes / 2;
	selectedNodeSlider = totalNodes / 2;
}

// Creates selected node coordinate label. Must be called after adjusting selectedNodeID.
string ofApp::makeSelectedCordLabel() const
{
	return "(" + to_string((int)graph->getCordsFromID(selectedNodeID).first) + "," + to_string((int)graph->getCordsFromID(selectedNodeID).second) + ")";
}

void ofApp::drawArrow(std::pair<float, float> nodeCords, string label) const
{
	const float r = 3.0 * 4.5; // node radius * size multiplier
	//ofSetLineWidth(2*r); // squared arrows
	ofSetLineWidth(r);
	ofDrawTriangle(nodeCords.first, nodeCords.second - .5 * r, nodeCords.first + r, nodeCords.second - 1.5 * r, nodeCords.first - r, nodeCords.second - 1.5 * r);
	ofDrawLine(nodeCords.first, nodeCords.second - 1.5 * r, nodeCords.first, nodeCords.second - 2.5 * r);
	ofSetColor(255);
	ofDrawBitmapString(label, nodeCords.first - 4 * label.length(), nodeCords.second - 3 * r);
}

// -------------------------------- Events --------------------------------

void ofApp::keyPressed(int key)
{
	// Selected node navigation
	if (key == OF_KEY_LEFT)
		selectedNodeSlider = selectedNodeSlider == 0 ? totalNodes - 1 : selectedNodeSlider - 1;
	else if (key == OF_KEY_RIGHT)
		selectedNodeSlider = (selectedNodeSlider + 1) % totalNodes;
}

void ofApp::keyReleased(int key)
{
	// Set source and target nodes
	if (key == OF_KEY_UP)
		sourceNodeSlider = selectedNodeID;
	else if (key == OF_KEY_DOWN)
		targetNodeSlider = selectedNodeID;

	// Gui toggling
	else if (key == OF_KEY_TAB)
	{
		if (showHelp && showSettings && showResults)
		{
			showAllMenus = false;
			showHelp = false;
			showSettings = false;
			showResults = false;
		}
		else if (!showHelp && !showSettings && !showResults)
		{
			showAllMenus = true;
			showHelp = true;
			showSettings = true;
			showResults = true;
		}
		else
		{
			showAllMenus = !showAllMenus;
			showHelp = showAllMenus;
			showSettings = showAllMenus;
			showResults = showAllMenus;
		}
	}
	else if (key == 'h' || key == 'H')
		showHelp = !showHelp;
	else if (key == 's' || key == 'S')
		showSettings = !showSettings;
	else if (key == 'r' || key == 'R')
		showResults = !showResults;

	// Run visualization
	else if (key == OF_KEY_RETURN)
		generateGraph(100); // TEMPORARY
}	

void ofApp::mouseMoved(int x, int y)
{

}

void ofApp::mouseDragged(int x, int y, int button)
{

}

void ofApp::mousePressed(int x, int y, int button)
{

}

void ofApp::mouseReleased(int x, int y, int button)
{
	// Update selected node gui elements
	if (button == 0) // Left mouse
	{
		unsigned int selected = graph->getSelectedNodeID(x, y);
		if (selected != -1)
			selectedNodeSlider = selected;
	}
}

void ofApp::mouseEntered(int x, int y)
{

}

void ofApp::mouseExited(int x, int y)
{

}

void ofApp::windowResized(int w, int h)
{

}

void ofApp::gotMessage(ofMessage msg)
{

}

void ofApp::dragEvent(ofDragInfo dragInfo)
{

}