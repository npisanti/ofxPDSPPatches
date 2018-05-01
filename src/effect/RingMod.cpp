
// RingMod.cpp
// Nicola Pisanti, MIT License, 2018

#include "RingMod.h"

void ofx::patch::effect::RingMod::patch(){
    
    addModuleInput( "0", rm0 );
    addModuleInput( "1", rm1 );
    
    addModuleOutput( "0", wet0 );
    addModuleOutput( "1", wet1 );
    addModuleInput( "pitch", sine.in_pitch() );
    
    pitchControl >> sine.in_pitch();
                    sine >> rm0.in_mod() >> wet0.in_1();
                    sine >> rm1.in_mod() >> wet1.in_1();
    
    wetControl >> wet0.in_fade();
    wetControl >> wet1.in_fade();
    
    parameters.setName( "ring modulator" );
    parameters.add( pitchControl.set( "pitch", 72, 0, 148) );
    parameters.add( wetControl.set( "depth amt", 0.5f, 0.0f, 1.0f) );
    
    smoothing(50.0f);
}

void ofx::patch::effect::RingMod::smoothing( float ms ){
    pitchControl.enableSmoothing( ms );
}

ofParameterGroup & ofx::patch::effect::RingMod::label( std::string name ){
    parameters.setName(name);
    return parameters;
}

pdsp::Patchable& ofx::patch::effect::RingMod::in_0() {
    return in("0");
}

pdsp::Patchable& ofx::patch::effect::RingMod::in_1() {
    return in("1");
}

pdsp::Patchable& ofx::patch::effect::RingMod::out_0() {
    return out("0");
}

pdsp::Patchable& ofx::patch::effect::RingMod::out_1() {
    return out("1");
}

pdsp::Patchable& ofx::patch::effect::RingMod::in_L() {
    return in("0");
}

pdsp::Patchable& ofx::patch::effect::RingMod::in_R() {
    return in("1");
}

pdsp::Patchable& ofx::patch::effect::RingMod::out_L() {
    return out("0");
}

pdsp::Patchable& ofx::patch::effect::RingMod::out_R() {
    return out("1");
}

pdsp::Patchable& ofx::patch::effect::RingMod::in_pitch() {
    return in("pitch");
}

