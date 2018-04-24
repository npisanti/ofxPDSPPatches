
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace synth {

class SinePercussion : public pdsp::Patchable{ 
public:
    SinePercussion(){ patch(); }
    SinePercussion(const SinePercussion & other){ patch(); }

    void longerEnvelopes();

    void enableDB( float minValue=-18.0f );
    void disableDB( );
    
    float meter() const ;

    pdsp::Patchable & in_trig();
    pdsp::Patchable & in_pitch();

    ofParameterGroup parameters;

    ofParameterGroup & label( string name );

private:
    void patch();

    pdsp::PatchNode     triggers;
    pdsp::FMOperator    osc;
    pdsp::AHR           aEnv;
    pdsp::AHR           pEnv;
    pdsp::Amp           amp;
    pdsp::Amp           pModAmt;

    ofxPDSPValue        fbModControl;
    ofxPDSPValue        fbControl;
    pdsp::Amp           fbModAmt;
    
    ofxPDSPValue        pitchControl;    
    ofxPDSPValue        veloToEnv;
    ofxPDSPValue        pEnvAmtControl;
    ofxPDSPValue        pEnvAttackControl;
    ofxPDSPValue        pEnvReleaseControl;

    ofxPDSPValue        envAttackControl;
    ofxPDSPValue        envHoldControl;
    ofxPDSPValue        envReleaseControl;

    pdsp::Amp           gain;
    pdsp::DBtoLin       dBtoLin;
    ofxPDSPValue        gainControl;  

};

}}} // end namespaces
