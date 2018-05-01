#pragma once

#include "ofMain.h"
#include "ofxPDSPPatches.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void exit();

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
    
    ofxPDSPEngine       engine;
    ofxPanel            gui;
    ofxPanel            samples;

    ofx::patch::synth::GrainDrone      drone;
    ofx::patch::util::SampleControl      sample0;
    ofx::patch::util::SampleControl      sample1;
    ofx::patch::util::SampleControl      sample2;
    ofx::patch::util::SampleControl      sample3;

};

