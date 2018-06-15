
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace effect {
    
class Ducker : public pdsp::Patchable {

public:    
    Ducker() { patch(); }
    Ducker( const Ducker & other ) { patch (); }
    
    ofParameterGroup parameters;

    float meter_env() const;

    pdsp::Patchable & in_trig();
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
        
    pdsp::Ducker ducker;
    
    pdsp::Parameter    attackControl;
    pdsp::Parameter    holdControl;
    pdsp::Parameter    releaseControl;
    pdsp::Parameter    duckingControl;
    pdsp::Parameter    veloControl;
    
};
    
}}}
