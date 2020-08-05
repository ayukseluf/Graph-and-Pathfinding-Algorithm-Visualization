#pragma once

#include <string>
#include "ofMain.h" // Required library
#include "ofxGui.h" // Required addon
#include "Graph.h"

class ofApp : public ofBaseApp
{
	Graph* graph;

	// Animation objects
	std::vector<Edge> shortestPath;
	std::stack<Edge> toBeDrawn; 

	// Menu values
	unsigned int totalNodes;
	unsigned int selectedNodeID;
	unsigned int sourceNodeID;
	unsigned int targetNodeID;
	float totalWeight; // of shortest path
	float elapsedTime; // of dijkstra's algorithim execution
	float idealTime; // required to travel from source to target
	float velocity;
	float currentEdgeWeight; // Weight of the edge currently being drawn
	float accumulativeTotalWeight; // Total weight of shortestPath drawn

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

	// Results menu
	ofxGuiGroup resultsGui;
	ofxLabel currentEdgeWeightLabel;
	ofxLabel totalEdgeWeightLabel;
	ofxLabel spacer4;
	ofxLabel idealTimeLabel;
	ofxLabel actualTimeLabel;
	ofxLabel timeDeltaLabel;
	ofxLabel spacer5;
	ofxLabel dijRuntimeLabel;

	// Primary Functions
	void setup();
	void update();
	void draw();

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
	void drawShortestPath(int delay);
	std::string makeSelectedCordLabel() const;
	void drawArrow(std::pair<float, float> nodeCords, string label) const;
	std::string floatToStringTruncated(float value, int decimalPlaces) const;

	// Input Events
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseReleased(int x, int y, int button);
};