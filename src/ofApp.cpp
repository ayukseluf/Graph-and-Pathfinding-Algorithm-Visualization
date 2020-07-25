#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup()
{
	ofBackground(80);
	
	for (int i = 0; i < 1000; i++) // Temp
	{
		Node* t = new Node();
		map.insert(std::pair<int, Node*>(i, t));
	}

	ofxGuiSetDefaultWidth(guiElementWidth);
	ofxGuiSetDefaultHeight(guiElementHeight);

	helpGui.setup("Help");
	helpGui.setPosition(ofGetWidth() - guiElementWidth - 5, 190);
	helpGui.add(keyBinding1.setup("Toggle All", "     tab"));
	helpGui.add(keyBinding2.setup("Toggle Help", "    h"));
	helpGui.add(keyBinding3.setup("Toggle Settings", "s"));
	helpGui.add(keyBinding4.setup("Toggle Results", " r"));
	helpGui.add(keyBinding5.setup("Quit","           esc"));

	settingsGui.setup("Settings");
	settingsGui.setPosition(ofGetWidth() - guiElementWidth - 5, 370);
	settingsGui.add(totalNodes.setup("Total Nodes", 100, 10, 1000));
	settingsGui.add(stackOverflowNodes.setup("100k Nodes", false));
	settingsGui.add(spacer1.setup("",""));
	settingsGui.add(sourceNode.setup("Source Node ID", 2, 1, totalNodes));
	settingsGui.add(locateSource.setup("Locate"));
	settingsGui.add(targetNode.setup("Target Node ID", 10, 1, totalNodes));
	settingsGui.add(locateTarget.setup("Locate"));
	settingsGui.add(spacer2.setup("", ""));
	settingsGui.add(selectedNode.setup("Selected Node", 1, 1, totalNodes));
	settingsGui.add(selectedCordLabel.setup("Coordinates","(X,Y)"));
	settingsGui.add(setSource.setup("Set as Source"));
	settingsGui.add(setTarget.setup("Set as Target"));
	settingsGui.add(spacer3.setup("", ""));
	settingsGui.add(animationSpeed.setup("Animation Speed", 1.0, .1, 10));
	settingsGui.add(velocity.setup("Velocity", 20, .1, 100));
	settingsGui.add(timeLimit.setup("Time Limit", 500, 1, 1000));

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
void ofApp::draw()
{
	for (int i = 0; i < totalNodes; i++) // Temp
		map.at(i)->draw();

	if(showHelp)
		helpGui.draw();
	if(showSettings)
		settingsGui.draw();
	if(showResults)
		resultsGui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
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
