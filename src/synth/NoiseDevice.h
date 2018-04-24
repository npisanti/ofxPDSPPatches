
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace synth {
    
class NoiseDevice : public pdsp::Patchable {

public:
    NoiseDevice(){ patch(); };
    NoiseDevice(const NoiseDevice & other){ patch(); };
    
    ofParameterGroup parameters;

    float meter() const;
    
    pdsp::Patchable & in_trig();
    pdsp::Patchable & in_pitch();
    pdsp::Patchable & in_cutoff();
    pdsp::Patchable & in_decimate();
    
    pdsp::Patchable & out_0();
    pdsp::Patchable & out_1();

    pdsp::Patchable & out_L();
    pdsp::Patchable & out_R();

    ofParameterGroup & label( string name );

private:
    void patch();
    
    pdsp::BitNoise          noise;
    pdsp::AHR               modEnv;

    pdsp::AHR               ampEnv;
    pdsp::Amp               amp0;
    pdsp::Amp               amp1;
    pdsp::PatchNode         trigger;
    
    pdsp::VAFilter          filter;
    ofxPDSPValue            filterTypeControl;
    ofxPDSPValue            filterCutoffControl;
    ofxPDSPValue            filterResoControl;
    
    ofxPDSPValue            noisePitchControl;
    ofxPDSPValue            noiseDecimateControl;
    
    ofxPDSPValue            envAttackControl;
    ofxPDSPValue            envHoldControl;
    ofxPDSPValue            envReleaseControl;
    
    ofxPDSPValue            modEnvVeloControl;
    ofxPDSPValue            modEnvAttackControl;
    ofxPDSPValue            modEnvReleaseControl;
    ofxPDSPValueMultiplier  modFilterAmt;
    ofxPDSPValueMultiplier  modPitchAmt;
    ofxPDSPValueMultiplier  modDecimateAmt;


    ofxPDSPValue            bitsControl;
    ofxPDSPValue            randomControl;
    ofxPDSPValue            randomCutoffControl;
    pdsp::TriggeredRandom   random0;    
    pdsp::TriggeredRandom   random1;    
    pdsp::TriggeredRandom   random2;    
    pdsp::Amp               randomPitch;
    pdsp::Amp               randomCutoff;
    pdsp::Amp               randomDecimate;
    

    pdsp::Amp           gain0;
    pdsp::Amp           gain1;
    pdsp::DBtoLin       dBtoLin;
    ofxPDSPValue        gainControl;  

};
    
}}} // end namespaces
