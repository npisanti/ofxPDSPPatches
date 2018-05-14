
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

#if !defined(OF_TARGET_ANDROID) || !defined(OF_TARGET_IOS)
#include "ofxWatchFile.h"
#endif 

namespace ofx { namespace patch { namespace sequencer {
    
    

class Tracker : public pdsp::Sequence{

    class Step {
    public:
        Step();
        
        float value;
        float chance;
    };

public:
    Tracker();

    void load( std::string filepath, bool autoreload=true );

    ofParameterGroup parameters;
        ofParameter<int>    division;
        ofParameter<int>    steps;
        ofParameter<int>    start;
        ofParameter<bool>   regenerate; // if this parameter is true regenerate the pattern at the next iteration (and then set himself to false again)
        ofParameter<bool>   autogenerate; // regenerate the pattern after <repeat> iterations
        ofParameter<int>    repeat; // how many times the pattern will be repeated before being generate again when autogenerate is true
        
private:

    void loadFile();

#if !defined(OF_TARGET_ANDROID) || !defined(OF_TARGET_IOS)    
    ofxWatchFile watcher;
    void onFileChange( ofFile &file ){
        loadFile();
    }
#endif 

    std::string path;

    std::vector<std::vector<std::vector<Step>>> values;
    std::atomic<int> index;
    
    bool bLoaded;
    
};

typedef Tracker PTracker;

}}} // end namespaces
