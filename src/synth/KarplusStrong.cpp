
// KarplusSynth.cpp
// Nicola Pisanti, MIT License, 2018

#include "KarplusStrong.h"


void ofx::patch::synth::KarplusStrong::Voice::patch() {
    addModuleInput("trig", triggers); 
    addModuleInput("pitch", comb.in_pitch() ); 
    addModuleInput("damping", comb.in_damping() ); 
    addModuleInput("fb", fbBoundaries );
    addModuleInput("pluck_attack", pluckEnv.in_attack() );
    addModuleInput("pluck_decay", pluckEnv.in_release() );

    addModuleInput("filter_type", filter.in_mode() );
    addModuleInput("filter_cutoff", filter.in_cutoff() );
    addModuleInput("filter_reso", filter.in_reso() );
    addModuleInput("filter_mod", filterEnvAmt.in_mod() );
    addModuleInput("mod_decay", filterEnv.in_release() );
    addModuleInput("mod_velo", filterEnv.in_velocity() );
    addModuleOutput("signal", comb ); 

    fbBoundaries.enableBoundaries(0.0f, 1.0f);
    fbBoundaries >> comb.in_fb();
    pluckEnv.enableDBTriggering(-24.0f, 0.0f);
    //patching
    gateEnv.set(0.0f, 0.0f, 1.0f, 20.0f);
    0.0f >> gateEnv.in_velocity();
    gateEnv >> fbBoundaries;
    
    filterEnv.set(0.0f, 0.0f, 30.f);
    pluckEnv.set(0.0f, 0.0f, 30.f);
        
    triggers >> gateEnv;    
    triggers >>                           pluckEnv >> noiseAmp.in_mod();
                                    noise >> filter>> noiseAmp >> comb;
    triggers >> filterEnv >> filterEnvAmt >> filter.in_cutoff();        
                                        
}

void ofx::patch::synth::KarplusStrong::setup ( int numVoices ) {
    
    voices.resize( numVoices );
    
    for( size_t i=0; i<voices.size(); ++i ){
        // connect each voice to chorus
        voices[i] >> chorus.in_0();
        voices[i] >> chorus.in_1();
        fbControl       >> voices[i].in("fb");
        dampingControl  >> voices[i].in("damping");
        pluckAttackControl >> voices[i].in("pluck_attack");
        pluckDecayControl >> voices[i].in("pluck_decay");
        filterModeControl >> voices[i].in("filter_type");
        filterCutoffControl >> voices[i].in("filter_cutoff");
        filterResoControl >> voices[i].in("filter_reso");
        filterModControl >> voices[i].in("filter_mod");
        filterModDecayControl >> voices[i].in("mod_decay");
        filterModVeloControl >> voices[i].in("mod_velo");
        
    }

    // set up chorus
    chorus.out_0() >> ampL;
    chorus.out_1() >> ampR;

    chorusSpeed >> chorus.in_speed();
    chorusDepth >> chorus.in_depth();
    
    masterFader >> dBtoLin >> ampL.in_mod();
                   dBtoLin >> ampR.in_mod();
    
    
    parameters.setName("karplus synth");
    parameters.add(masterFader.set( "master dB", -12, -48, 0 ) );
    parameters.add(pluckAttackControl.set( "pluck attack", 0, 0, 500 ) );
    parameters.add(pluckDecayControl.set( "pluck decay", 30, 1, 500 ) );
    parameters.add(fbControl.set( "feedback", 0.99f, 0.75f, 1.0f ) );
    parameters.add(dampingControl.set( "damping", 0.0f, 0.0f, 0.99f ) );
    parameters.add(filterModeControl.set( "filter mode", 0, 0, 5 ) );
    parameters.add(filterCutoffControl.set( "filter cutoff", 136, 20, 136 ) );
    parameters.add(filterResoControl.set( "filter reso", 0.0f, 0.0f, 1.0f ) );
    parameters.add(filterModControl.set( "filter mod", 0, 0, 120 ) );
    parameters.add(filterModDecayControl.set( "mod decay", 30, 1, 500 ) );
    parameters.add(filterModVeloControl.set( "mod dyn", 0.5f, 0.0f, 1.0f ) );
    
    
    parameters.add(chorusSpeed.set("cho speed (hz)", 0.25f, 0.25f, 1.0f));
    parameters.add(chorusDepth.set("cho depth (ms)", 3.5f, 1.0f, 8.0f));
    
    
    masterFader.enableSmoothing(50.0f);
    fbControl.enableSmoothing(50.0f);
    dampingControl.enableSmoothing(50.0f);
    
}


size_t ofx::patch::synth::KarplusStrong::size() {
    return voices.size();
}


pdsp::Patchable & ofx::patch::synth::KarplusStrong::in_trig( int voice ) {
    return voices[voice].in("trig");
}
pdsp::Patchable & ofx::patch::synth::KarplusStrong::in_pitch( int voice ) {
    return voices[voice].in("pitch");
}
    
pdsp::Patchable & ofx::patch::synth::KarplusStrong::out_L() {
    return ampL;
}

pdsp::Patchable & ofx::patch::synth::KarplusStrong::out_R() {
    return ampR;
}
