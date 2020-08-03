#pragma once

#include <iostream>
#include <string>
#include "ofMain.h" // Required library
#include "ofxGui.h" // Required addon
#include "Graph.h"

class ofApp : public ofBaseApp
{
	Graph* graph;

	// Menu values
	unsigned int totalNodes;
	unsigned int selectedNodeID;
	unsigned int sourceNodeID;
	unsigned int targetNodeID;

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
	ofxLabel keyBinding6;
	ofxLabel keyBinding7;
	ofxLabel keyBinding8;
	ofxLabel keyBindingLast;

	// Settings menu
	ofxGuiGroup settingsGui;
	ofxLabel spacer1;
	ofxLabel spacer2;
	ofxLabel spacer3;
	ofxLabel selectedCordLabel; 
	ofxButton _125NodeButton;
	ofxButton _250NodeButton;
	ofxButton _500NodeButton;
	ofxButton _1000NodeButton;
	ofxButton maxNodeButton; // 100,000 nodes
	ofxButton setSourceButton;
	ofxButton setTargetButton;
	ofxButton launchAnimationButton;
	ofxToggle highlightSourceTargetToggle; 
	ofxToggle highlightSelectedToggle;

	// These sliders double as primitve type variables. i.e. the totalNode variable can also
	// be treated and used as an integer that stores the total number of nodes
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

	// Listeners
	void sourceNodeSliderChanged(int& sourceNode);
	void targetNodeSliderChanged(int& targetNode);
	void selectedNodeSliderChanged(int& selectedNode);
	void setSourceButtonPressed();
	void setTargetButtonPressed();
	void _125NodeButtonPressed();
	void _250NodeButtonPressed();
	void _500NodeButtonPressed();
	void _1000NodeButtonPressed();
	void maxNodeButtonPressed();
	void launchAnimationButtonPressed();

	// Helper Functions
	void generateGraph(unsigned int totalNodes);
	string makeSelectedCordLabel() const;
	void drawArrow(std::pair<float, float> nodeCords, string label) const;

	// Events
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};