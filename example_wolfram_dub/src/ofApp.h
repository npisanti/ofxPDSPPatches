#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxPDSPPatches.h"
#include "ofxGui.h"

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

        void switchRule();

        // pdsp modules
        pdsp::Engine   engine; 
        
        ofx::patch::sequence::Wolfram wolframSeq;
        ofx::patch::effect::BasiVerb reverb;
        
        std::vector<ofx::patch::synth::SinePercussion> zaps;
        
        pdsp::ParameterGain dubSwitch;

        ofx::patch::effect::StereoDelay dub;

        pdsp::Sequence     masterplan;
        pdsp::LowCut       revCut;

        ofxPanel gui;
        
        int caHeight;
        
        ofParameter<bool> masterplanRandomize;
        ofParameter<int> randomizeBars;
        
        ofColor brightColor;
        ofColor darkColor;
        
        vector<pdsp::Scope> scopes;
        
};



