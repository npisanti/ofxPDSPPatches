#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxPDSP.h"
#include "ofxPDSPPatches.h"
#include "ofxGui.h"
#include "voice.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        
        void drawMeter(float value, float min, float max, int x, int y, int w, int h);
        
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
        
        pdsp::Engine   engine;

        SynthVoice monosynth;
        
        pdsp::ParameterGain    fader;
        
        pdsp::midi::Input        midiIn;
        pdsp::midi::Keys         midiKeys;

        ofx::patch::effect::BasiVerb       reverb;
        
        pdsp::OneBarTimeMs   barMs;
    
        pdsp::DampedDelay    delay1;
        pdsp::DampedDelay    delay2;
        
        ofx::patch::effect::Chorus  chorus;
        ofx::patch::effect::StereoDelay  delays;
        
        pdsp::Parameter      attack;
        
        ofxPanel             gui;
    
};
