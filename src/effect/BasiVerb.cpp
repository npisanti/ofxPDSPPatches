
// BasiVerb.cpp
// Nicola Pisanti, MIT License, 2018

#include "BasiVerb.h"

void ofx::patch::effect::BasiVerb::patch(){

	reverb.out_L() >> gain.in_L();
	reverb.out_R() >> gain.in_R();	
	
	timeControl 		>> reverb.in_time();
    densityControl 		>> reverb.in_density();
    dampingControl 		>> reverb.in_damping();
    hiCutControl 		>> reverb.in_hi_cut();
    modFreqControl 		>> reverb.in_mod_freq();
    modAmountControl 	>> reverb.in_mod_amount();
    
    parameters.setName( "reverb" );
    parameters.add( gain.set("reverb gain", -24, -48, 12 ) );
    parameters.add( timeControl.set("rt60", 3.33f, 0.05f, 20.0f ) );
    parameters.add( densityControl.set("density", 0.85f, 0.0f, 1.0f ) );
    parameters.add( dampingControl.set("damping", 0.25f, 0.0f, 1.0f ) );
    parameters.add( hiCutControl.set("high cut freq", 8000, 3000, 20000 ) );
    parameters.add( modFreqControl.set("mod speed (hz)", 0.5f, 0.25f, 8.25f));
    parameters.add( modAmountControl.set("mod depth (ms)", 0.0f, 0.0f, 3.0f));
}

ofParameterGroup & ofx::patch::effect::BasiVerb::label( string name ){
    parameters.setName( name );
    return parameters;
}

float ofx::patch::effect::BasiVerb::meter_lfo() const {
    return reverb.meter_lfo();
}

pdsp::Patchable & ofx::patch::effect::BasiVerb::in() {
    return reverb.in_signal();
}

pdsp::Patchable & ofx::patch::effect::BasiVerb::in_signal() {
    return reverb.in_signal();
}

pdsp::Patchable & ofx::patch::effect::BasiVerb::out_0() {
    return gain.out_L();
}

pdsp::Patchable & ofx::patch::effect::BasiVerb::out_1() {
    return gain.out_R();
}

pdsp::Patchable & ofx::patch::effect::BasiVerb::out_L() {
    return gain.out_L();
}

pdsp::Patchable & ofx::patch::effect::BasiVerb::out_R() {
    return gain.out_R();
}

