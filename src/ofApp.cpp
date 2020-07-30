#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup()
{
	graph = nullptr;
	generateGraph(1000);
	
	// Intialization
	showAllMenus = true;
	showHelp = true;
	showSettings = true;
	showResults = true;

	// Styling
	ofBackground(80);
	guiElementWidth = 250; // TODO: need to scale gui with window size
	guiElementHeight = 20;
	ofxGuiSetDefaultWidth(guiElementWidth);
	ofxGuiSetDefaultHeight(guiElementHeight);

	// Help Gui
	helpGui.setup("Help");
	helpGui.setPosition(ofGetWidth() - guiElementWidth - 5, 190);
	helpGui.add(keyBinding1.setup("Toggle All", "     tab"));
	helpGui.add(keyBinding2.setup("Toggle Help", "    h"));
	helpGui.add(keyBinding3.setup("Toggle Settings", "s"));
	helpGui.add(keyBinding4.setup("Toggle Results", " r"));
	helpGui.add(keyBinding5.setup("Quit","           esc"));

	// Settings Gui
	settingsGui.setup("Settings");
	settingsGui.setPosition(ofGetWidth() - guiElementWidth - 5, 370);
	settingsGui.add(totalNodesSlider.setup("Total Nodes", totalNodes, 10, 1000));
	settingsGui.add(stackOverflowNodes.setup("100k Nodes", false));
	settingsGui.add(spacer1.setup("",""));
	settingsGui.add(sourceNodeSlider.setup("Source Node ID", 2, 0, totalNodes - 1));
	settingsGui.add(locateSource.setup("Locate"));
	settingsGui.add(targetNodeSlider.setup("Target Node ID", 10, 0, totalNodes - 1));
	settingsGui.add(locateTarget.setup("Locate"));
	settingsGui.add(spacer2.setup("", ""));
	settingsGui.add(selectedNodeSlider.setup("Selected Node", selectedNodeID, 0, totalNodes - 1));
	settingsGui.add(selectedCordLabel.setup("Coordinates", makeSelectedCordLabel()));
	settingsGui.add(setSource.setup("Set as Source"));
	settingsGui.add(setTarget.setup("Set as Target"));
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

//--------------------------------------------------------------
void ofApp::update()
{
	
}

//--------------------------------------------------------------
void ofApp::draw() // Code not directly related to drawing should be placed in the update function
{
	graph->drawNodes();

	if(showHelp)
		helpGui.draw();
	if(showSettings)
		settingsGui.draw();
	if(showResults)
		resultsGui.draw();
}

//--------------------------------------------------------------
void ofApp::generateGraph(short totalNodes)
{
	if (graph)
		delete graph;

	graph = new Graph(totalNodes);

	this->totalNodes = totalNodes;
	totalNodesSlider = totalNodes;
	selectedNodeID = totalNodes / 4;
	selectedNodeSlider = selectedNodeID;
	selectedCordLabel = makeSelectedCordLabel();
}

//--------------------------------------------------------------
// Must be called after adjusting selectedNodeID
string ofApp::makeSelectedCordLabel() const
{
	return "(" + to_string((int)graph->getCordsFromID(selectedNodeID).first) + "," + to_string((int)graph->getCordsFromID(selectedNodeID).second) + ")";
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	// Gui toggling
	if (key == OF_KEY_TAB)
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
	else if (key == 'n')
		generateGraph(100); // TEMP
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	// Update selected node gui elements
	if (button == 0) // Left mouse
	{
		short selected = graph->getSelectedNodeID(x, y);
		if (selected != -1)
		{
			selectedNodeID = selected;
			selectedCordLabel = makeSelectedCordLabel();
			selectedNodeSlider = selectedNodeID;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}