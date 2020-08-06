#include "ofApp.h"

void ofApp::setup()
{
	graph = nullptr;
	generateGraph(125);
	
	// Show menus
	showAllMenus = true;
	showHelp = true;
	showSettings = true;
	showResults = true;

	// Styling
	ofFill();
	ofBackground(49, 68, 85);
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
	launchAnimationButton.addListener(this, &ofApp::launchAnimationButtonPressed);

	// Help Gui
	helpGui.setup("Help");
	helpGui.setPosition(ofGetWidth() - guiElementWidth - 5, 100);
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
	settingsGui.setPosition(ofGetWidth() - guiElementWidth - 5, 320);
	settingsGui.add(_125NodeButton.setup("125 Nodes"));
	settingsGui.add(_250NodeButton.setup("250 Nodes"));
	settingsGui.add(_500NodeButton.setup("500 Nodes"));
	settingsGui.add(_1000NodeButton.setup("1,000 Nodes"));
	settingsGui.add(maxNodeButton.setup("100,000 Nodes (No Graphics)"));
	settingsGui.add(spacer1.setup("",""));
	settingsGui.add(sourceNodeSlider.setup("Source Node ID", sourceNodeID, 0, totalNodes - 1));
	settingsGui.add(targetNodeSlider.setup("Target Node ID", targetNodeID, 0, totalNodes - 1));
	settingsGui.add(highlightSourceTargetToggle.setup("Highlight", true));
	settingsGui.add(spacer2.setup("", ""));
	settingsGui.add(selectedNodeSlider.setup("Selected Node", selectedNodeID, 0, totalNodes - 1));
	settingsGui.add(selectedCordLabel.setup("Coordinates", makeSelectedCordLabel()));
	settingsGui.add(highlightSelectedToggle.setup("Highlight", false));
	settingsGui.add(setSourceButton.setup("Set as Source"));
	settingsGui.add(setTargetButton.setup("Set as Target"));
	settingsGui.add(spacer3.setup("", ""));
	settingsGui.add(animationSpeedSlider.setup("Animation Speed", 1, .1, 2));
	settingsGui.add(velocitySlider.setup("Velocity", 20, .1, 100));
	settingsGui.add(launchAnimationButton.setup("Launch Animation"));

	// Results Gui
	resultsGui.setup("Results");
	resultsGui.setPosition(ofGetWidth() - guiElementWidth - 5, 750);
	resultsGui.add(currentEdgeWeightLabel.setup("Current Edge Weight", ""));
	resultsGui.add(totalEdgeWeightLabel.setup("Total Edge Weight", ""));
	resultsGui.add(spacer4.setup("", ""));
	resultsGui.add(idealTimeLabel.setup("Ideal Travel Time",""));
	resultsGui.add(actualTimeLabel.setup("Actual Travel Time",""));
	resultsGui.add(timeDeltaLabel.setup("Travel Time Delta", ""));
	resultsGui.add(showIdealPathToggle.setup("Show Ideal Path", false));
	resultsGui.add(spacer5.setup("", ""));
	resultsGui.add(dijRuntimeLabel.setup("Dijkstra Runtime", ""));
}

void ofApp::update()
{
	// Force highlighters on for 100k nodes
	if(totalNodes == 100000) 
	{
		highlightSourceTargetToggle = true;
		highlightSelectedToggle = true;
	}

	// Update results after animation concluded
	if (toBeDrawn.empty() && shortestPath.size() > 0)
	{
		std::string spacer = "          "; // Used to align labels relative to each other

		// Actual time -> weight of best path / velocity
		std::string actualTimeString = floatToStringTruncated(totalWeight / velocity, 2);
		actualTimeLabel = spacer.substr(0, spacer.length() - actualTimeString.length() - 1) + actualTimeString; 

		// Ideal time -> straight line distance between source and target / velocity
		std::string idealTimeString = floatToStringTruncated(idealTime, 2);
		idealTimeLabel = spacer.substr(0, spacer.length() - idealTimeString.length()) + idealTimeString; 

		// Delta -> actual time - ideal time
		std::string delta = floatToStringTruncated(stof(actualTimeString) - stof(idealTimeString), 2);
		timeDeltaLabel = spacer.substr(0, spacer.length() - delta.length()) + delta;

		// Dijkstras runtime
		dijRuntimeLabel = spacer.substr(0, spacer.length() - idealTimeString.length() + 1) + to_string((int)elapsedTime) + " ms";

		// Current Edge Weight
		currentEdgeWeightLabel = "";
	}

	// Update results during animation
	if (!toBeDrawn.empty())
	{
		std::string spacer = "          "; // Used to align labels relative to each other
		
		// Acumulative Total Weight
		std::string totalWeightString = floatToStringTruncated(accumulativeTotalWeight, 2);
		totalEdgeWeightLabel = spacer.substr(0, spacer.length() - totalWeightString.length()) + totalWeightString;

		// Current Edge Weight
		std::string currentEdgeWeightString = floatToStringTruncated(currentEdgeWeight, 2);
		currentEdgeWeightLabel = spacer.substr(0, spacer.length() - currentEdgeWeightString.length() - 2) + currentEdgeWeightString;
	}
}

void ofApp::draw()
{
	// Edges
	ofSetColor(158, 90, 99);
	ofSetLineWidth(2);
	if(totalNodes < 100000)
		graph->drawEdges();

	// Nodes
	ofSetColor(151, 170, 189);
	if(totalNodes < 100000)
		graph->drawNodes();

	// Shortest Path
	ofSetColor(254, 249, 199);
	ofSetLineWidth(3);
	drawShortestPath(21 - int(animationSpeedSlider * 10));

	// Ideal Path
	ofSetColor(254, 208, 0);
	ofSetLineWidth(3);
	if (showIdealPathToggle)
		ofDrawLine(graph->getCordsFromID(sourceNodeID).first, graph->getCordsFromID(sourceNodeID).second, graph->getCordsFromID(targetNodeID).first, graph->getCordsFromID(targetNodeID).second);


	// Highlighters
	if (highlightSourceTargetToggle)
	{
		ofSetColor(219, 54, 3);
		drawArrow(graph->getCordsFromID(targetNodeID), "To");
		ofSetColor(3, 219, 54);
		drawArrow(graph->getCordsFromID(sourceNodeID), "From");
	}
	if (highlightSelectedToggle)
	{
		ofSetColor(254, 208, 0);
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
	if (toBeDrawn.empty())
	{
	sourceNodeID = sourceNode;
	shortestPath.clear();
	}
}

void ofApp::targetNodeSliderChanged(int& targetNode)
{
	if (toBeDrawn.empty())
	{
		targetNodeID = targetNode;
		shortestPath.clear();
	}
}

void ofApp::selectedNodeSliderChanged(int& selectedNode)
{
	if (toBeDrawn.empty())
	{
		selectedNodeID = selectedNode;
		selectedCordLabel = makeSelectedCordLabel();
		highlightSelectedToggle = true;
	}
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
	if (toBeDrawn.empty())
		generateGraph(125);
}

void ofApp::_250NodeButtonPressed()
{
	if (toBeDrawn.empty())
		generateGraph(250);
}
void ofApp::_500NodeButtonPressed()
{
	if (toBeDrawn.empty())
		generateGraph(500);
}

void ofApp::_1000NodeButtonPressed()
{
	if (toBeDrawn.empty())
		generateGraph(1000);
}

void ofApp::maxNodeButtonPressed()
{
	if (toBeDrawn.empty())
		generateGraph(100000);
}

void ofApp::launchAnimationButtonPressed()
{
	// Reset values from previous shortest path
	shortestPath.clear();
	totalWeight = 0;
	accumulativeTotalWeight = 0;
	idealTimeLabel = "";
	actualTimeLabel = "";
	timeDeltaLabel = "";
	dijRuntimeLabel = "";

	// Call Dijkstra only if source node changed since last call
	if (sourceNodeID != graph->getLastSourceNodeID())
	{
		ofResetElapsedTimeCounter();
		graph->Dijkstra(sourceNodeID);
		elapsedTime = ofGetElapsedTimeMillis();
	}
	velocity = velocitySlider;
	idealTime = ofDist(graph->getCordsFromID(sourceNodeID).first, graph->getCordsFromID(sourceNodeID).second, graph->getCordsFromID(targetNodeID).first, graph->getCordsFromID(targetNodeID).second) / velocity;
	// Push all edges in the shortest path to toBeDrawn
	toBeDrawn = graph->establishPath(targetNodeID);
}

// --------------------------- Helper Functions ---------------------------

void ofApp::generateGraph(unsigned int numNodes)
{
	// Delete previous graph
	delete graph;
	shortestPath.clear();

	// Load graph from file
	if (numNodes == 125)
		graph = new Graph(numNodes, "data/125-B.txt");
	else if (numNodes == 250)
		graph = new Graph(numNodes, "data/250-B.txt");
	else if (numNodes == 500)
		graph = new Graph(numNodes, "data/500-B.txt");
	else if (numNodes == 1000)
		graph = new Graph(numNodes, "data/1000-B.txt");
	else if (numNodes == 100000)
		graph = new Graph(numNodes, "data/100000-A.txt");

	// Update ofApp values
	totalNodes = numNodes;

	bool toggled = highlightSelectedToggle;

	sourceNodeSlider.setMax(totalNodes - 1);
	sourceNodeID = totalNodes / 4;
	sourceNodeSlider = sourceNodeID;

	targetNodeSlider.setMax(totalNodes - 1);
	targetNodeID = totalNodes / 4 * 3;
	targetNodeSlider = targetNodeID;
	
	selectedNodeSlider.setMax(totalNodes - 1);
	selectedNodeID = totalNodes / 2;
	selectedNodeSlider = totalNodes / 2;

	highlightSelectedToggle = toggled;
}

// Draws edges in shortestPath. Animation effect created by popping edges off of to be drawn stack every "delay" frames.
void ofApp::drawShortestPath(int delay)
{
	// Push edges to shortestPath with delay
	if (!toBeDrawn.empty() && ofGetFrameNum() % delay == 0)
	{
		shortestPath.push_back(toBeDrawn.top());
		currentEdgeWeight = toBeDrawn.top().getWeight();
		totalWeight += toBeDrawn.top().getWeight();
		accumulativeTotalWeight = totalWeight;
		toBeDrawn.pop();
	}

	// Draw edges in shortestPath
	for (Edge edge : shortestPath)
	{
		std::pair<float, float> from = graph->getCordsFromID(edge.getFrom());
		std::pair<float, float> to = graph->getCordsFromID(edge.getTo());
		ofDrawLine(from.first, from.second, to.first, to.second);
	}
}

// Creates selected node coordinate label. Must be called after adjusting selectedNodeID.
std::string ofApp::makeSelectedCordLabel() const
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
	
	// Unlabled rectangular arrow
	if (label == "")
		ofDrawRectangle(nodeCords.first - 13.5, nodeCords.second - 33.75 * yOffset, 27, 13.5 * yOffset);

	// Labeled standard arrow
	else
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


// Converts floats to a string with truncated decimal places
std::string ofApp::floatToStringTruncated(float value, int decimalPlaces) const
{
	return to_string(value).substr(0, to_string(value).find('.') + decimalPlaces + 1);
}

// -------------------------------- Input Events --------------------------------

void ofApp::keyPressed(int key)
{
	// Selected node navigation
	if (key == OF_KEY_LEFT)
	{
		highlightSelectedToggle = true;
		selectedNodeSlider = selectedNodeSlider == 0 ? totalNodes - 1 : selectedNodeSlider - 1; // Loops at min value
	}
	else if (key == OF_KEY_RIGHT)
	{
		highlightSelectedToggle = true;
		selectedNodeSlider = (selectedNodeSlider + 1) % totalNodes; // Loops at max values
	}
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
		launchAnimationButtonPressed();
}	

void ofApp::mouseReleased(int x, int y, int button)
{
	// Update selected node gui elements
	if (button == 0) // Left mouse
	{
		unsigned int selected = graph->getSelectedNodeID(x, y);
		if (selected != -1) // Value of selected if no node at click position
			selectedNodeSlider = selected;
	}
}