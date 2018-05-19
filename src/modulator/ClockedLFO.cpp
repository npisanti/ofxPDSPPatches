
// ClockedLFO.cpp
// Nicola Pisanti, MIT License, 2018

#include "ClockedLFO.h"


ofParameterGroup & ofx::patch::modulator::ClockedLFO::label( std::string name ){
    parameters.setName(name);
    return parameters;
}

ofParameterGroup & ofx::patch::modulator::ClockedLFO::setup( std::string name, float multiply ){
    multiplier.set( "amount", multiply, 0.0f, multiply );
    parameters.setName(name);
    return parameters;
}

void ofx::patch::modulator::ClockedLFO::patch(){
    
    addModuleInput( "phase",  lfo.in_phase_offset() );
    addModuleOutput( "signal", multiplier );
    
    divisionControl >> lfo.in_division();
    phaseControl >> lfo.in_phase_offset();
    
    lfoSwitch >> multiplier;
    
    modeControl >> lfoSwitch.in_select();
    
    lfoSwitch.resize(5);  // resize input channels
    lfo.out_triangle()          >> lfoSwitch.input(0); // you cannot use this input() method in a chain
    lfo.out_saw()               >> lfoSwitch.input(1); // because: API reasons
    lfo.out_square()            >> lfoSwitch.input(2);
    lfo.out_sine()              >> lfoSwitch.input(3);
    lfo.out_sample_and_hold()   >> lfoSwitch.input(4);
    
    parameters.setName( "clocked LFO" );
    divide.addListener( this, &ClockedLFO::recalculateDivision );
    pulse.addListener(  this, &ClockedLFO::recalculateDivision );

    parameters.add( divide.set( "divide", 1, 1, 16) );
    parameters.add( pulse.set( "pulse", 4, 1, 16) );

    parameters.add( phaseControl.set( "phase", 0.0f, 0.0f, 1.0f) );
    parameters.add( modeControl.set( "shape", 0, 0, 4) );
    parameters.add( multiplier.set( "amount", 1.0f, 0.0f, 1.0f) );
        
}

float ofx::patch::modulator::ClockedLFO::meter_output() const {
    return lfoSwitch.meter_output();
}

void ofx::patch::modulator::ClockedLFO::recalculateDivision( int & value ) {
    divisionControl.setv( static_cast<float>(divide) / static_cast<float> (pulse) );
}


void ofx::patch::modulator::ClockedLFO::setShape( int value ) {
    if( value >=0 && value < 5){
        modeControl.getOFParameterInt() = value;        
    }else{
        ofLogError()<<"[clocked lfo] wrong index for shape";
    }
}

void ofx::patch::modulator::ClockedLFO::setPulse( int value ) {
    pulse = value;
}

void ofx::patch::modulator::ClockedLFO::setDivide( int value ) {
    divide = value;
}

void ofx::patch::modulator::ClockedLFO::setAmount( float value  ) {
    multiplier.getOFParameterFloat() = value;
}
