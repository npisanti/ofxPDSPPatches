
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace effect {  
    
class BasiVerb {

public:    
    BasiVerb() { patch(); }
    BasiVerb( const BasiVerb & other ) { patch (); }
    
    ofParameterGroup parameters;

    float meter_lfo() const;

    pdsp::Patchable & in();
    pdsp::Patchable & in_signal();
    pdsp::Patchable & out_0();
    pdsp::Patchable & out_1();
    pdsp::Patchable & out_L();
    pdsp::Patchable & out_R();

    ofParameterGroup & label( string name );
    
private:    
    void patch();
        
    pdsp::BasiVerb 	reverb;
    ofxPDSPStereoFader	gain;
    ofxPDSPValue    timeControl;
    ofxPDSPValue    densityControl;
    ofxPDSPValue    dampingControl;
    ofxPDSPValue    hiCutControl;
    ofxPDSPValue    modFreqControl;
    ofxPDSPValue    modAmountControl;
    
};
    
}}}
