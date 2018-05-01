
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace modulator { 
    
class ClockedLFO : public pdsp::Patchable {

public:    
    ClockedLFO() { patch(); }
    ClockedLFO( const ClockedLFO & other ) { patch (); }
    
    ofParameterGroup parameters;

    ofParameterGroup & label( std::string name );  
    
    float meter_output() const;

    void setShape( int value );
    void setPulse( int value );
    
private:    
    void patch();
    void recalculateDivision( int & value );
        
    pdsp::ClockedLFO    lfo;
    ofParameter<int>    pulse;
    ofParameter<int>    divide;
    ofxPDSPValue        amountControl;
    ofxPDSPValue        phaseControl;
    ofxPDSPValue        modeControl;

    pdsp::Switch        lfoSwitch;
    ofxPDSPValue        divisionControl;
    
    pdsp::BipolarToUnipolar b2u;
    
};
    
}}} // end namespaces 
