
// PitchTable.cpp
// Nicola Pisanti, MIT License, 2018

#include "PitchTable.h"

ofParameterGroup & ofx::patch::tuning::PitchTable::setup( int size, std::string name ) {
    
    pitch.resize( size );
    
    parameters.setName( name );

    int index = 0;
    
    for( ofxPDSPValue & p : pitch ){

        string label = "p";
        label += ofToString(index+1);
        label += " coarse";
        parameters.add( p.set( label, 36, 24, 108 ) );

        label = "p";
        label += ofToString(index+1);
        label += " fine";
        parameters.add( p.set( label, 0.0f, -0.5f, 0.5f ) );

        index++;
    }
    
    return parameters;
}

ofParameterGroup & ofx::patch::tuning::PitchTable::label( std::string name ){
    parameters.setName( name );
    return parameters;
}
    
void ofx::patch::tuning::PitchTable::set( int i, float pitch ) {
    int pInt = pitch;
    float fract = pitch - (float) pInt;
    this->pitch[i].getOFParameterInt().set(pInt);
    this->pitch[i].getOFParameterFloat().set(fract);
}

void ofx::patch::tuning::PitchTable::smoothing( float ms ) {
    for( ofxPDSPValue & p : pitch ) p.enableSmoothing( ms );
}

size_t ofx::patch::tuning::PitchTable::size() const {
    return pitch.size();
}
