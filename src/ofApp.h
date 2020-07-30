#pragma once

#include <iostream>
#include <string>
#include "ofMain.h" // Required library
#include "ofxGui.h" // Required addon
#include "Graph.h"

class ofApp : public ofBaseApp
{
	Graph* graph;

	short totalNodes;
	short selectedNodeID;

	// Menu visibility
	bool showAllMenus;
	bool showHelp;
	bool showSettings;
	bool showResults;

	// Styling
	float guiElementWidth;
	float guiElementHeight;
		
	// Help menu
	ofxGuiGroup helpGui;
	ofxLabel keyBinding1;
	ofxLabel keyBinding2;
	ofxLabel keyBinding3;
	ofxLabel keyBinding4;
	ofxLabel keyBinding5;

	// Settings menu
	ofxGuiGroup settingsGui;
	ofxLabel spacer1;
	ofxLabel spacer2;
	ofxLabel spacer3;
	ofxLabel selectedCordLabel; // Displays selected node's coordinates
	ofxButton setSource; // Indicates selected node should be set as source when true
	ofxButton setTarget; // Indicates  selected node shoulb be set as target when true
	ofxButton locateSource; // Source should be highlighted when true
	ofxButton locateTarget; // Target should be highlighted when true
	ofxToggle stackOverflowNodes; // Indicates that 100k nodes should be drawn when true

	// These sliders double as primitve type variables. i.e. the totalNode variable can also
	// be treated and used as an integer that stores the total number of nodes
	ofxIntSlider totalNodesSlider;  
	ofxIntSlider sourceNodeSlider; 
	ofxIntSlider targetNodeSlider; 
	ofxIntSlider selectedNodeSlider; 
	ofxFloatSlider animationSpeedSlider; 
	ofxFloatSlider velocitySlider; 
	ofxFloatSlider timeLimitSlider; 

	// Results menu
	ofxGuiGroup resultsGui;
	ofxLabel idealTimeLabel;
	ofxLabel actualTimeLabel;
	ofxLabel timeDeltaLabel;

	// Helper functions
	void generateGraph(short totalNodes);
	string makeSelectedCordLabel() const;

	// Core OF functions
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
