
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace effect {

class StereoDelay : public pdsp::Patchable {

public:
    StereoDelay() { patch(); };
    StereoDelay(const StereoDelay & other) { patch(); };
    
    ofParameterGroup parameters;

    ofxPDSPValueMultiplier  lDelayTimeControl;
    ofxPDSPValueMultiplier  rDelayTimeControl;
    ofxPDSPValue            lFeedbackControl;
    ofxPDSPValue            rFeedbackControl;

    pdsp::Patchable & in_0();
    pdsp::Patchable & in_1();
    pdsp::Patchable & out_0();
    pdsp::Patchable & out_1();

    pdsp::Patchable & in_L();
    pdsp::Patchable & in_R();
    pdsp::Patchable & out_L();
    pdsp::Patchable & out_R();

    ofParameterGroup & label( string name );

private:
    void patch();

    pdsp::LFOPhazor         phazor;
    pdsp::CheapTri          LFO;
    ofxPDSPValueMultiplier  modAmt;
    ofxPDSPValue            speed;

    pdsp::DampedDelay ldelay;
    pdsp::DampedDelay rdelay;
    
    pdsp::OneBarTimeMs time;

    ofxPDSPValue dampingControl;
    
    ofxPDSPStereoFader input;
    ofxPDSPStereoFader output;
    
};

}}} // end namespaces
