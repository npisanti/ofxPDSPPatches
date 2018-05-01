
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx{ namespace patch { namespace util {
    
class SampleControl : public pdsp::Patchable {
public:
    SampleControl() { patch(); } 
    SampleControl( const SampleControl & other ) { patch(); } 
    
    void load(string path);

    ofParameterGroup    parameters;
    pdsp::SampleBuffer  sample;    
    
    bool normalize;
    
    ofxSampleBufferPlotter  graphics;
    
    bool loading() const;
    
    ofParameterGroup & label( std::string name );
    
private:
    void patch ();

    void loadButtonCall( bool & value );
    void sampleChangedCall( string & value );
    void loadSample( string path );
    
    ofParameter<bool>   loadButton;
    ofParameter<string> samplePath;
    ofParameter<string> sampleName;
    
    static int number;
};   
    
}}} // end namespaces
