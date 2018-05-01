
// Filter.cpp
// Nicola Pisanti, MIT License, 2018

#include "Filter.h"

void ofx::patch::effect::Filter::patch(){
    
    addModuleInput( "0", filter.in_0() );
    addModuleInput( "1", filter.in_1() );
    
    addModuleOutput( "0", filter.out_0() );
    addModuleOutput( "1", filter.out_1() );
    addModuleInput( "cutoff", filter.in_cutoff() );
    
    cutoffControl    >> filter.in_cutoff();
    resoControl      >> filter.in_reso();
    
    parameters.setName( "filter" );
    parameters.add( cutoffControl.set( "cutoff", 136, 20, 136) );
    parameters.add( resoControl.set( "reso", 0.0f, 0.0f, 1.0f) );
    parameters.add( modeControl.set( "filter type", 0, 0, 5) );
    
    smoothing(50.0f);
}

ofParameterGroup & ofx::patch::effect::Filter::label( std::string name ){
    parameters.setName(name);
    return parameters;
}

float ofx::patch::effect::Filter::meter_cutoff() const {
    return filter.meter_cutoff();
}

pdsp::Patchable& ofx::patch::effect::Filter::in_cutoff() {
    return in("cutoff");
}

void ofx::patch::effect::Filter::smoothing( float ms ){
    cutoffControl.enableSmoothing( ms );
    resoControl.enableSmoothing( ms );
}

pdsp::Patchable & ofx::patch::effect::Filter::in_0() {
    return in("0");
}

pdsp::Patchable & ofx::patch::effect::Filter::in_1() {
    return in("1");
}

pdsp::Patchable & ofx::patch::effect::Filter::out_0() {
    return out("0");
}

pdsp::Patchable & ofx::patch::effect::Filter::out_1() {
    return out("1");
}

pdsp::Patchable & ofx::patch::effect::Filter::in_L() {
    return in("0");
}

pdsp::Patchable & ofx::patch::effect::Filter::in_R() {
    return in("1");
}

pdsp::Patchable & ofx::patch::effect::Filter::out_L() {
    return out("0");
}

pdsp::Patchable & ofx::patch::effect::Filter::out_R() {
    return out("1");
}
