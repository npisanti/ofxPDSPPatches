
// Cruncher.cpp
// Nicola Pisanti, MIT License, 2018

#include "Cruncher.h"

void ofx::patch::effect::Cruncher::patch(){
    
    addModuleInput( "0", decimate0 );
    addModuleInput( "1", decimate1 );
    
    addModuleOutput( "0", bitcrunch0 );
    addModuleOutput( "1", bitcrunch1 );
    addModuleInput( "mod", cutoffModAmt );
    
    cutoffControl >> p2f >> decimate0.in_freq();
                     p2f >> decimate1.in_freq();
                     
    bitsControl      >> bitcrunch0.in_bits();
    bitsControl      >> bitcrunch1.in_bits();
    
    cutoffModAmt     >> p2f;
    cutoffModControl >> cutoffModAmt.in_mod();
    
    decimate0 >> bitcrunch0;
    decimate1 >> bitcrunch1;
    
    parameters.setName( "cruncher" );
    parameters.add( cutoffControl.set( "decimate", 152, 20, 148) );
    parameters.add( cutoffModControl.set( "decimate mod", 0, 0, 127) );
    parameters.add( bitsControl.set( "bits", 24, 24, 1) );
    
    smoothing(50.0f);
}

ofParameterGroup & ofx::patch::effect::Cruncher::label( std::string name ){
    parameters.setName(name);
    return parameters;
}

float ofx::patch::effect::Cruncher::meter_decimate_pitch() const {
    return p2f.meter_input();
}

pdsp::Patchable& ofx::patch::effect::Cruncher::in_decimate_mod() {
    return in("mod");
}

void ofx::patch::effect::Cruncher::smoothing( float ms ){
    cutoffControl.enableSmoothing( ms );
    bitsControl.enableSmoothing( ms );
}

pdsp::Patchable & ofx::patch::effect::Cruncher::in_0() {
    return in("0");
}

pdsp::Patchable & ofx::patch::effect::Cruncher::in_1() {
    return in("1");
}

pdsp::Patchable & ofx::patch::effect::Cruncher::out_0() {
    return out("0");
}

pdsp::Patchable & ofx::patch::effect::Cruncher::out_1() {
    return out("1");
}

pdsp::Patchable & ofx::patch::effect::Cruncher::in_L() {
    return in("0");
}

pdsp::Patchable & ofx::patch::effect::Cruncher::in_R() {
    return in("1");
}

pdsp::Patchable & ofx::patch::effect::Cruncher::out_L() {
    return out("0");
}

pdsp::Patchable & ofx::patch::effect::Cruncher::out_R() {
    return out("1");
}
