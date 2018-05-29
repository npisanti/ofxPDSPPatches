
// Ducker.cpp
// Nicola Pisanti, MIT License, 2018

#include "Ducker.h"

void ofx::patch::effect::Ducker::patch(){

    addModuleInput( "0", ducker.in_0() );
    addModuleInput( "1", ducker.in_1() );
    addModuleInput( "trig", ducker.in_trig() );
    addModuleOutput( "0", ducker.out_0() );
    addModuleOutput( "1", ducker.out_1() );
    
    attackControl  >> ducker.in_attack();
    holdControl    >> ducker.in_hold();
    releaseControl >> ducker.in_release();
    duckingControl >> ducker.in_ducking();
    veloControl    >> ducker.in_velocity();
    
    parameters.setName( "ducker" );
    parameters.add(duckingControl.set("ducking", -12, -48, 0) );
    parameters.add(attackControl.set("attack", 50, 10, 600));
    parameters.add(holdControl.set("hold", 0, 10, 600));
    parameters.add(releaseControl.set("release", 100, 20, 1200));
    parameters.add(veloControl.set("sensitivity", 0.0f, 0.0f, 1.0f));
}

ofParameterGroup & ofx::patch::effect::Ducker::label( std::string name ){
    parameters.setName(name);
    return parameters;
}

float ofx::patch::effect::Ducker::meter_env() const {
    return ducker.meter_env();
}

pdsp::Patchable & ofx::patch::effect::Ducker::in_0() {
    return in("0");
}

pdsp::Patchable & ofx::patch::effect::Ducker::in_1() {
    return in("1");
}

pdsp::Patchable & ofx::patch::effect::Ducker::out_0() {
    return out("0");
}

pdsp::Patchable & ofx::patch::effect::Ducker::out_1() {
    return out("1");
}

pdsp::Patchable & ofx::patch::effect::Ducker::in_L() {
    return in("0");
}

pdsp::Patchable & ofx::patch::effect::Ducker::in_R() {
    return in("1");
}

pdsp::Patchable & ofx::patch::effect::Ducker::out_L() {
    return out("0");
}

pdsp::Patchable & ofx::patch::effect::Ducker::out_R() {
    return out("1");
}

pdsp::Patchable & ofx::patch::effect::Ducker::in_trig() {
    return in("trig");
}
