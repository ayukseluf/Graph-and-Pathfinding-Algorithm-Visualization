#include "ofApp.h"

void ofApp::setup()
{
	graph = nullptr;
	generateGraph(1000);
	for(unsigned int i = 0; i < 1000; i++)
	{
		std::vector<unsigned int> vecForNode;
		map.emplace(make_pair(i, vecForNode));
	}
	for(unsigned int i = 0; i < 1000; i++)
	{
		int j = 0;
		while(j < 1000)
		{
			int numNodes = 0;
			if( ofDist(graph->nodes[i].getX(), graph->nodes[i].getY(), graph->nodes[j].getX(), graph->nodes[j].getY() ) <= 60 && ofDist(graph->nodes[i].getX(), graph->nodes[i].getY(), graph->nodes[j].getX(), graph->nodes[j].getY() ) > 5)
			// edge generation with a radius rule
			{
				map[i].push_back(j);
				map[j].push_back(i);
				numNodes++;
			}
			if(numNodes == 2) // This number needs to go down as radius increases
			{
				break;
			}
			j++;
		}
	}
	// Intialization
	showAllMenus = true;
	showHelp = true;
	showSettings = true;
	showResults = true;

	// Styling
	ofFill();
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
	_125NodeButton.addListener(this, &ofApp::_125NodeButtonPressed);
	_250NodeButton.addListener(this, &ofApp::_250NodeButtonPressed);
	_500NodeButton.addListener(this, &ofApp::_500NodeButtonPressed);
	_1000NodeButton.addListener(this, &ofApp::_1000NodeButtonPressed);
	maxNodeButton.addListener(this, &ofApp::maxNodeButtonPressed);

	// Help Gui
	helpGui.setup("Help");
	helpGui.setPosition(ofGetWidth() - guiElementWidth - 5, 150);
	helpGui.add(keyBinding1.setup("Toggle All", "     tab"));
	helpGui.add(keyBinding2.setup("Toggle Help", "    h"));
	helpGui.add(keyBinding3.setup("Toggle Settings", "s"));
	helpGui.add(keyBinding4.setup("Toggle Results", " r"));
	helpGui.add(keyBinding5.setup("Selected Node", "  left / right"));
	helpGui.add(keyBinding6.setup("Set Source Node", "up"));
	helpGui.add(keyBinding7.setup("Set Target Node", "down"));
	helpGui.add(keyBinding8.setup("Start Animation", "enter"));
	helpGui.add(keyBindingLast.setup("Quit","           esc"));

	// Settings Gui
	settingsGui.setup("Settings");
	settingsGui.setPosition(ofGetWidth() - guiElementWidth - 5, 370);
	settingsGui.add(_125NodeButton.setup("125 Nodes"));
	settingsGui.add(_250NodeButton.setup("250 Nodes"));
	settingsGui.add(_500NodeButton.setup("500 Nodes"));
	settingsGui.add(_1000NodeButton.setup("1,000 Nodes"));
	settingsGui.add(maxNodeButton.setup("100,000 Nodes (No Graphics)"));
	settingsGui.add(spacer1.setup("",""));
	settingsGui.add(sourceNodeSlider.setup("Source Node ID", sourceNodeID, 0, totalNodes - 1));
	settingsGui.add(targetNodeSlider.setup("Target Node ID", targetNodeID, 0, totalNodes - 1));
	settingsGui.add(highlightSourceTargetToggle.setup("Highlight", false));
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
	settingsGui.add(launchAnimationToggle.setup("Launch Animation", false));

	// Results Gui
	resultsGui.setup("Results");
	resultsGui.setPosition(ofGetWidth() - guiElementWidth - 5, 900);
	resultsGui.add(idealTimeLabel.setup("Ideal Time Taken","   0:00"));
	resultsGui.add(actualTimeLabel.setup("Actual Time Taken","  0:00"));
	resultsGui.add(timeDeltaLabel.setup("Inefficiency Delta", " 0:00"));
}

void ofApp::update()
{
	if(totalNodes == 100000) // Force highlighters on for 100k nodes
	{
		highlightSourceTargetToggle = true;
		highlightSelectedToggle = true;
	}
}

// --- TEMP
void ofApp::printData()
{
	// std::cout << "fromID, x, y, toID, weight, toID, weight, ... " << std::endl;
	string str = "";
	std::ofstream fileOutput("data/1000-B.txt");
	for (auto it = map.begin(); it != map.end(); it++) // altered to output to file instead due to console output being too long
	{
		str = to_string(it->first) + " " + to_string(graph->getCordsFromID(it->first).first) + " " + to_string(graph->getCordsFromID(it->first).second);
		for (unsigned int i : it->second)
			str += " " + to_string(i) + " " + to_string(ofDist(graph->getCordsFromID(it->first).first, graph->getCordsFromID(it->first).second, graph->getCordsFromID(i).first, graph->getCordsFromID(i).second));
		fileOutput << str << std::endl;
	}
}

void ofApp::draw()
{
	// Graph
	ofSetColor(3, 218, 198);
	if(totalNodes < 100000)
		graph->drawNodes();

	// TEMP
	ofSetLineWidth(2);
	for (auto it = map.begin(); it != map.end(); it++)
	{
		for (unsigned int i : it->second)
			ofDrawLine(graph->getCordsFromID(it->first).first, graph->getCordsFromID(it->first).second, graph->getCordsFromID(i).first, graph->getCordsFromID(i).second);
	}

	// Highlighters
	if (highlightSourceTargetToggle)
	{
		ofSetColor(255, 0, 0);
		drawArrow(graph->getCordsFromID(targetNodeID), "To");
		ofSetColor(0, 255, 0);
		drawArrow(graph->getCordsFromID(sourceNodeID), "From");
	}
	if (highlightSelectedToggle)
	{
		ofSetColor(255, 255, 0);
		drawArrow(graph->getCordsFromID(selectedNodeID), "");
	}

	// Menus
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

void ofApp::_125NodeButtonPressed()
{
	generateGraph(125);
}

void ofApp::_250NodeButtonPressed()
{
	generateGraph(250);
}
void ofApp::_500NodeButtonPressed()
{
	generateGraph(500);
}

void ofApp::_1000NodeButtonPressed()
{
	generateGraph(1000);
}

void ofApp::maxNodeButtonPressed()
{
	generateGraph(100000);
}

// --------------------------- Helper Functions ---------------------------

void ofApp::generateGraph(unsigned int numNodes)
{
	delete graph;
	std::string fileName = "";
	if(numNodes == 125)
	{
		fileName = "data/125-A.txt";
	} else if(numNodes == 1000)
	{
		fileName = "data/1000-C.txt";
	} else if (numNodes == 500)
	{
		fileName = "data/500-A.txt";
	} else if (numNodes == 250)
	{
		fileName = "data/250-A.txt";
	}
	graph = new Graph(fileName);
	
	totalNodes = numNodes;

	sourceNodeSlider.setMax(totalNodes - 1);
	sourceNodeID = totalNodes / 4;
	sourceNodeSlider = sourceNodeID;

	targetNodeSlider.setMax(totalNodes - 1);
	targetNodeID = totalNodes / 4 * 3;
	targetNodeSlider = targetNodeID;
	
	selectedNodeSlider.setMax(totalNodes - 1);
	selectedNodeID = totalNodes / 2;
	selectedNodeSlider = totalNodes / 2;

	// std::ifstream file("data/500-B.txt");
    // std::string line = "";
    // while(getline(file, line))
    // {
    //     stringstream edgeData(line);
    //     std::string sourceNode = "";
    //     getline(edgeData, sourceNode, ' ');
    //     std::string targetNode = "";
	// 	getline(edgeData, targetNode, ' ');
	// 	getline(edgeData, targetNode, ' ');
	// 	unsigned int source = (unsigned int) std::stoi(sourceNode);
    //     while(getline(edgeData, targetNode, ' '))
    //     {
	// 		unsigned int target = (unsigned int) std::stoi(targetNode);
	// 		map[source].push_back(target);
    // 		getline(edgeData, targetNode, ' ');

	// 	}

    // }
}

// Creates selected node coordinate label. Must be called after adjusting selectedNodeID.
string ofApp::makeSelectedCordLabel() const
{
	return "(" + to_string((int)graph->getCordsFromID(selectedNodeID).first) + "," + to_string((int)graph->getCordsFromID(selectedNodeID).second) + ")";
}

// Draws a labeled arrow at passed coordinates. Draws unlabeled rectangular arrow if passed "". Otherwise pass "From" or "To".
void ofApp::drawArrow(std::pair<float, float> nodeCords, string label) const
{
	float yOffset = 1;
	if (nodeCords.second <= 35.0) // Flip y axis if close to top
		yOffset = -1;

	ofDrawTriangle(nodeCords.first, nodeCords.second - 6.75 * yOffset, nodeCords.first + 13.5, nodeCords.second - 20.25 * yOffset, nodeCords.first - 13.5, nodeCords.second - 20.25 * yOffset);
	
	if (label == "") // Rectangular arrow
	{
		ofDrawRectangle(nodeCords.first - 13.5, nodeCords.second - 33.75 * yOffset, 27, 13.5 * yOffset);
	}

	else // Labeled arrow
	{
		ofSetLineWidth(13.5);
		ofDrawLine(nodeCords.first, nodeCords.second - 20.25 * yOffset, nodeCords.first, nodeCords.second - 33.75 * yOffset);
		ofSetColor(255);
		if (yOffset == -1) // Adjust for reversed text if close to top
			yOffset = -1.2;
		if(sourceNodeID == targetNodeID && label == "From") // Offset labels if both on same node
			ofDrawBitmapString(label, nodeCords.first - 4 * label.length(), nodeCords.second - 52.5 * yOffset);
		else
			ofDrawBitmapString(label, nodeCords.first - 4 * label.length(), nodeCords.second - 40.5 * yOffset);
	}
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
	/*else if (key == OF_KEY_RETURN) // TODO
		generateGraph(100); */

		// TEMP
	else if (key == 'e' || key == 'E')
		map[sourceNodeID].push_back(targetNodeID);
	else if (key == 'd' || key == 'D')
		printData();
	else if (key == 'Z')
	{
		for(unsigned int i = 0; i < map[sourceNodeID].size(); i++)
		{
			if(map[sourceNodeID][i] == targetNodeID)
			{
				map[sourceNodeID].erase(map[sourceNodeID].begin() + i);
			}
		}
	}
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