
// example_lead_reverb
// Nicola Pisanti, MIT License, 2018

// example to test BasiVerb and StereoDelay, 
// compile, play the keyboard and tweak the parameters

// requires a midi keyboard, remember to set the right port for midi

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowTitle("brass lead + rev/delay");
    engine.score.setTempo(86.0f); // the delay times are clocked

    midiKeys.setMonoMode(1, true);

    // activate portamento, in poly mode you can notice portamento only on note stealing
    midiKeys.setPortamento(On, 150.0f, pdsp::Rate);

    midiKeys.outs_trig[0]  >> monosynth.in("trig");
    midiKeys.outs_pitch[0] >> monosynth.in("pitch");
        
    attack >> monosynth.in("attack");
    monosynth >> fader;
    
    
    fader >> reverb.in();
    fader >> delays.in_L();
    fader >> delays.in_R();    

    delays.out_L() >> reverb.in();
    delays.out_R() >> reverb.in();
    
    fader >> engine.audio_out(0);
    fader >> engine.audio_out(1);
    
    reverb.out_0() >> engine.audio_out(0);
    reverb.out_1() >> engine.audio_out(1);
  
    delays.out_0() >> engine.audio_out(0);
    delays.out_1() >> engine.audio_out(1);
  
    // graphic setup---------------------------
    ofSetVerticalSync(true);
    ofDisableAntiAliasing();
    ofBackground(0);
    ofSetColor(ofColor(0,100,100));
    ofNoFill();
    ofSetLineWidth(1.0f);
    ofSetFrameRate(24);

    // GUI -----------------------------------
    gui.setHeaderBackgroundColor(ofColor( 40, 0, 0));
    gui.setBorderColor(ofColor(40, 0, 0));
    
    gui.setDefaultFillColor(ofColor(255, 85, 85));
    gui.setDefaultBackgroundColor(ofColor(0,0,0));

    gui.setup("gui", "settings.xml", 20, 20);
    gui.add( fader.set("synth gain", -6, -48, 24) );
    gui.add( attack.set("attack", 350.0f, 20.0f, 700.0f));
    gui.add( reverb.parameters );
    gui.add( delays.parameters );
    gui.loadFromFile("settings.xml");
    
    // audio setup----------------------------
    // for our midi controllers to work we have to add them to the engine, so it know it has to process them
    midiIn.listPorts();
    midiIn.openPort(1); //set the right port !!!
    engine.addMidiController( midiKeys, midiIn ); // add midi processing to the engine
    engine.listDevices();
    engine.setDeviceID(0); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
    engine.setup( 44100, 512, 3);     
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
