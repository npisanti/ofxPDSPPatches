
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace synth {
    
class QuickSampler : public pdsp::Patchable {
public:
    QuickSampler() { patch(); } 
    QuickSampler( const QuickSampler & other ){ patch(); } 
    
    ofParameterGroup    parameters;
    
    pdsp::Patchable & in_trig();
    pdsp::Patchable & in_pitch();
    
    pdsp::Patchable & out_0();
    pdsp::Patchable & out_1();

    pdsp::Patchable & out_L();
    pdsp::Patchable & out_R();

    void dBTriggering( bool enable );
    void load(string path);
    
    ofParameterGroup & label( std::string name );
    
private:
    void patch();

    void loadButtonCall( bool & value );
    void sampleChangedCall( std::string & value );
    void loadSample( std::string path );
    


    pdsp::PatchNode     triggers;
    pdsp::Sampler       sampler0;
    pdsp::Sampler       sampler1;
    pdsp::AHR           env;
    pdsp::AHR           fEnv;
    pdsp::Amp           amp0;
    pdsp::Amp           amp1;
    
    pdsp::Amp           fader0;
    pdsp::Amp           fader1;
    pdsp::DBtoLin       dBtoLin;
    ofxPDSPValue        faderControl;    
    
    pdsp::OnePole       lp0a;
    pdsp::OnePole       lp0b;
    pdsp::OnePole       lp1a;
    pdsp::OnePole       lp1b;
    
    pdsp::TriggeredRandom   drift;
    pdsp::Amp               driftAmt;
    ofxPDSPValue            driftControl;
    
    pdsp::PatchNode         pitchNode;
    ofxPDSPValue            pitchControl;
        
    ofxPDSPValue        startControl;
    ofxPDSPValue        startModControl;
        
    ofxPDSPValue        attackControl;
    ofxPDSPValue        holdControl;
    ofxPDSPValue        releaseControl;
    
    ofxPDSPValue        envFilterControl;
    pdsp::Amp           envFilterAmt;
    ofxPDSPValue        filterControl;
    pdsp::PitchToFreq   p2f;
    
    ofxPDSPValue        envDynControl;

    pdsp::SampleBuffer  sample;    
    ofParameter<bool>   loadButton;
    ofParameter<string> samplePath;
    ofParameter<string> sampleName;
    
};   
    
}}} // end namespaces 