

#pragma once

#include "ofxPDSP.h"
#include "ofMain.h"

namespace ofx { namespace patch { namespace synth {


class KarplusStrong {
    
// ----------------------------------------------------------------------------------------------------------------------------
public:

class Voice : public pdsp::Patchable{ 
public:
    Voice() { patch(); }
    Voice(const Voice & other) { patch(); }

    void patch();
private:
    pdsp::PatchNode         fbBoundaries;
    pdsp::PatchNode         triggers;
    pdsp::PRNoiseGen        noise;
    pdsp::AHR               pluckEnv;
    pdsp::ADSR              gateEnv;
    pdsp::Amp               noiseAmp;
    
    pdsp::AHR               filterEnv;
    pdsp::Amp               filterEnvAmt;
    pdsp::VAFilter          filter;

    pdsp::CombFilter        comb;        
};    



    
public: // ---------------------- public API ----------------------------------    
    
    void setup ( int numVoices );
    
    pdsp::Patchable & in_trig( int voice );
    pdsp::Patchable & in_pitch( int voice );
    pdsp::Patchable & out_L();
    pdsp::Patchable & out_R();
    
    size_t size();

    ofParameterGroup parameters;
    
private: // -------------------------------------------------------------------  

    std::vector<Voice>           voices;
    
    pdsp::Amp               ampL;
    pdsp::Amp               ampR;
    
    ofxPDSPValue            masterFader;
    pdsp::DBtoLin           dBtoLin;
    
    pdsp::DimensionChorus   chorus;       

    ofxPDSPValue     fbControl;
    ofxPDSPValue     dampingControl;
    
    ofxPDSPValue     pluckAttackControl;
    ofxPDSPValue     pluckDecayControl;
    
    ofxPDSPValue     filterModeControl;
    ofxPDSPValue     filterCutoffControl;
    ofxPDSPValue     filterResoControl;
    ofxPDSPValue     filterModControl;
    ofxPDSPValue     filterModDecayControl;
    ofxPDSPValue     filterModVeloControl;

    ofxPDSPValue     chorusSpeed;
    ofxPDSPValue     chorusDepth;

};

}}} // end namespaces
