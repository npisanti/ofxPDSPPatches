#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxPDSPPatches.h"
#include "ofxGui.h"

//#define TEST_COMPRESSOR

class ofApp : public ofBaseApp{

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
        
        // pdsp modules
        pdsp::Engine   engine;
        
        ofx::patch::synth::QuickSampler loop;
     
        #ifdef TEST_COMPRESSOR
        ofx::patch::dynamics::Compressor dyn;
        #else
        ofx::patch::dynamics::Brickwall dyn;
        #endif
            
        ofxPanel gui;



};
