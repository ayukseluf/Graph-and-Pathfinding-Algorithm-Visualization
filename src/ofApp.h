#pragma once

#include "ofMain.h"
#include "ofxGui.h" // Required addon

#include "Node.h"

#include<map>
#include<utility>
#include<iostream>

class ofApp : public ofBaseApp{

		// Menu visibility
		bool showAllMenus = true;
		bool showHelp = true;
		bool showSettings = true;
		bool showResults = true;

		// Styling
		float guiElementWidth = 250;
		float guiElementHeight = 20;
		
		// Help Menu
		ofxGuiGroup helpGui;
		ofxLabel keyBinding1;
		ofxLabel keyBinding2;
		ofxLabel keyBinding3;
		ofxLabel keyBinding4;
		ofxLabel keyBinding5;

		// Settings Menu
		ofxGuiGroup settingsGui;
		ofxLabel spacer1;
		ofxLabel spacer2;
		ofxLabel spacer3;
		ofxLabel selectedCordLabel; // Displays selected node's coordinates.
		ofxButton setSource; // Indicates selected node should be set as source when true.
		ofxButton setTarget; // Indicates  selected node shoulb be set as target when true.
		ofxButton locateSource; // Source should be highlighted when true.
		ofxButton locateTarget; // Target should be highlighted when true.
		ofxToggle stackOverflowNodes; // Indicates that 100k nodes should be drawn when true.

		// These sliders double as primitve type variables. i.e. the totalNode variable should also
		// be treated and used as an integer that stores the total number of nodes.
		ofxIntSlider totalNodes;  
		ofxIntSlider sourceNode; 
		ofxIntSlider targetNode; 
		ofxIntSlider selectedNode; 
		ofxFloatSlider animationSpeed; 
		ofxFloatSlider velocity; 
		ofxFloatSlider timeLimit; 

		// Results Menu
		ofxGuiGroup resultsGui;
		ofxLabel idealTimeLabel;
		ofxLabel actualTimeLabel;
		ofxLabel timeDeltaLabel;

		std::map<int, Node*> map;
		
	public:
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
