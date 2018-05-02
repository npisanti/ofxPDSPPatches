
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxGui.h"

// wavetable based polysynth

namespace ofx { namespace patch { namespace synth {

class WaveSynth {

public:
    // class to rapresent each synth voice ------------
    class Voice : public pdsp::Patchable {
        friend class WaveSynth;
    
    public:
        Voice(){}
        Voice(const Voice& other){}

        pdsp::Patchable& in_trig();
        pdsp::Patchable& in_pitch();
        pdsp::Patchable& in_table();
        pdsp::Patchable& in_cutoff();
        
        float meter_mod_env() const;
        float meter_pitch() const;

    private:
        void setup(WaveSynth & m);

        pdsp::PatchNode     voiceTrigger;
        
        pdsp::TableOscillator   oscillator;
        pdsp::VAFilter          filter;
        pdsp::Amp               voiceAmp;


        pdsp::ADSR          envelope;    
        pdsp::Amp           envToTable;
        pdsp::Amp           envToFilter;  
                
        pdsp::Amp               driftAmt;
        pdsp::LFOPhazor         phazorFree;
        pdsp::TriggeredRandom   rnd;
        pdsp::OnePole           randomSlew;
    }; // end voice class -----------------------------


    // synth public API --------------------------------------
    ofParameterGroup & setup( int numVoice, float spread=0.0f, std::string name="wavesynth" );

    pdsp::Patchable& out_L();
    pdsp::Patchable& out_R();

    vector<Voice>       voices;
    ofParameterGroup    parameters;

    ofParameterGroup & label (std::string name );

    pdsp::WaveTable  wavetable;

private: // --------------------------------------------------

    ofxPDSPStereoFader gain;

    ofxPDSPValue     table_ctrl;

    ofxPDSPValue     cutoff_ctrl;
    ofxPDSPValue     reso_ctrl;
    ofxPDSPValue     filter_mode_ctrl;

    ofxPDSPValue     env_attack_ctrl;
    ofxPDSPValue     env_decay_ctrl;
    ofxPDSPValue     env_sustain_ctrl;
    ofxPDSPValue     env_release_ctrl;
    ofxPDSPValue     env_filter_ctrl;
    ofxPDSPValue     env_table_ctrl;
    ofxPDSPValue     drift;
};

}}} // end namspaces 
