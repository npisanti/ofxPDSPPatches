
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace effect { 
    
class Chorus {

public:    
    Chorus() { patch(); }
    Chorus( const Chorus & other ) { patch (); }
    
    ofParameterGroup parameters;

    float meter_lfo() const;

    pdsp::Patchable & in_0();
    pdsp::Patchable & in_1();
    pdsp::Patchable & out_0();
    pdsp::Patchable & out_1();
    pdsp::Patchable & in_L();
    pdsp::Patchable & in_R();
    pdsp::Patchable & out_L();
    pdsp::Patchable & out_R();

    ofParameterGroup & label( std::string name );

private:    
    void patch();
        
    pdsp::DimensionChorus chorus;
    pdsp::Parameter    speedControl;
    pdsp::Parameter    depthControl;

};
    
}}} // end namespaces 
