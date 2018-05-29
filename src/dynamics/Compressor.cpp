
// Compressor.cpp
// Nicola Pisanti, MIT License, 2018

#include "Compressor.h"

void ofx::patch::dynamics::Compressor::patch(){

    addModuleInput( "0", input0 );
    addModuleInput( "1", comp.in_1() );
    addModuleOutput( "0", makeup.out_0() );
    addModuleOutput( "1", makeup.out_1() );
    
    comp.RMS( 25.0f );
    comp.analog();
    
    input0 >> comp.in_0();
    comp.out_0() >> makeup.in_0();
    comp.out_1() >> makeup.in_1();

    attackControl       >> comp.in_attack();
    releaseControl      >> comp.in_release();
    thresholdControl    >> comp.in_threshold();
    ratioControl        >> comp.in_ratio(); 
    
    parameters.setName( "rms compressor" );
    parameters.add(thresholdControl.set("threshold", 0, 0, -24));
    parameters.add(attackControl.set("attack", 10, 1, 200));
    parameters.add(releaseControl.set("release", 48, 10, 1000));
    parameters.add(ratioControl.set("ratio", 2, 1, 12));
    parameters.add(kneeControl.set("knee", 0, 0, 6));
    parameters.add(makeup.set("makeup gain", 0, -6, 12));
}

void ofx::patch::dynamics::Compressor::enableScope( ofxPDSPEngine & engine ){   
    input0 >> scope >> engine.blackhole();
    scope.set(512*8); 
}
    
void ofx::patch::dynamics::Compressor::drawScope( int x, int y, int w, int h ) {
    ofPushMatrix();
    ofTranslate( x, y );
        ofDrawBitmapString( "limiter scope", 2, 14 );
        scope.draw( 0, 0, w, h);
        float yl = (1.0f-dB(threshold())) * h * 0.5f;        
        ofDrawLine(0, yl, w, yl );
        ofDrawLine(0, h-yl, w, h-yl );
    ofPopMatrix();
}

void ofx::patch::dynamics::Compressor::drawMeter( int x, int y, int w, int h ) {
    ofPushMatrix();
    ofTranslate( x, y );
        float wm = ofMap(comp.meter_GR(), 0, -9, 0, w );
        ofNoFill();
        ofDrawRectangle( 0, 0, w, h);
        ofFill();
        ofDrawRectangle( 0, 0, wm, h);
        float x0 = 220*0.33333333f;
        float x1 = 220*0.66666666f;
        ofDrawLine( x0, 0, x0, h );
        ofDrawLine( x1, 0, x1, h );
        
                
        ofDrawBitmapString( "GR", 2, 14 );
        ofDrawBitmapString( "3", x0-8, 14 );
        ofDrawBitmapString( "6", x1-8, 14 );
        ofDrawBitmapString( "9", w-8, 14 );
    ofPopMatrix();
}

void ofx::patch::dynamics::Compressor::draw( int x, int y, int w, int h ){
    int hscope = h - 30;
    drawScope( x, y, w, hscope );
    drawMeter( x, y+hscope+10, w, 20 );
}

ofParameterGroup & ofx::patch::dynamics::Compressor::label( std::string name ){
    parameters.setName(name);
    return parameters;
}

float ofx::patch::dynamics::Compressor::meter_GR() const {
    return comp.meter_GR();
}

pdsp::Patchable & ofx::patch::dynamics::Compressor::in_0() {
    return in("0");
}

pdsp::Patchable & ofx::patch::dynamics::Compressor::in_1() {
    return in("1");
}

pdsp::Patchable & ofx::patch::dynamics::Compressor::out_0() {
    return out("0");
}

pdsp::Patchable & ofx::patch::dynamics::Compressor::out_1() {
    return out("1");
}

pdsp::Patchable & ofx::patch::dynamics::Compressor::in_L() {
    return in("0");
}

pdsp::Patchable & ofx::patch::dynamics::Compressor::in_R() {
    return in("1");
}

pdsp::Patchable & ofx::patch::dynamics::Compressor::out_L() {
    return out("0");
}

pdsp::Patchable & ofx::patch::dynamics::Compressor::out_R() {
    return out("1");
}
