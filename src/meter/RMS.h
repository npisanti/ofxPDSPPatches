
#pragma once

#include "ofxPDSP.h"

namespace ofx { namespace patch { namespace meter {
	
class RMS : public pdsp::Patchable {

public:
    RMS(){ patch(); }
    RMS(const RMS & other){ patch(); }

    void patch();
    
    ofParameterGroup & label( string name );

    ofParameterGroup parameters;

    float meter() const;

    ofxPDSPValue     attackControl;
    ofxPDSPValue     releaseControl;
    ofxPDSPMonoFader gain;
    
private:
    pdsp::RMSDetector       rms;
    pdsp::EnvelopeFollower  envFollower;

    
};

}}} // end namespaces
