
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"


struct SynthVoice : public pdsp::Patchable {

public:        
    SynthVoice() { patch();}
    SynthVoice(const SynthVoice& other){ patch(); }

private:
    void patch(){

        addModuleInput("trig", voiceTrigger);
        addModuleInput("pitch", osc.in_pitch());
        addModuleInput("attack", ampEnv.in_attack());
        addModuleInput("fb", osc.in_fb());
        addModuleOutput("signal", voiceAmp);

        // SIGNAL PATH
        voiceTrigger >> ampEnv;
        
        ampEnv.set(500.0f, 7000.0f, 0.2f, 1200.0f ) * 0.5f >> voiceAmp.in_mod();
                                                     osc >> voiceAmp;
        ampEnv * 0.25f >> osc.in_fb();
        
    }

    pdsp::PatchNode     voiceTrigger;
    
    pdsp::VAOscillator  oscillator;

    pdsp::FMOperator    osc;

    pdsp::Amp           voiceAmp;
    
    pdsp::ADSR          ampEnv;
    pdsp::ADSR          modEnv;
    

 
};
