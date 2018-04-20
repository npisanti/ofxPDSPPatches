
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

namespace ofx{ namespace patch { namespace sequencer {

class Euclidean : public pdsp::Sequence {
    
public:
    Euclidean();
    
    ofParameter<float>   xJit;
    ofParameter<float>   x;
    ofParameter<float>   yJit;
    ofParameter<float>   y;
    
    
    ofParameter<int>     seqShift;
    ofParameter<int>     repeat;
    
    ofParameter<float>   ghostsChance;
    ofParameter<float>   ghostsDynMin;
    ofParameter<float>   ghostsDynMax;
    
    ofParameter<int>    steps;
    ofParameter<int>    division;
    
    ofParameter<bool>   remake;
    ofParameter<bool>   automake;
    ofParameter<float>  gate;        
        
    ofParameterGroup & label( std::string name );

    std::vector<float>   bars;
    
    ofParameterGroup parameters;
    
private:
    
    int gcd( int x, int y );
    // create a christoffel word by y/x, usally y rappresent the number of onsets
    // x has to be > y, or will be wrapped
    // usually is good to use x = n - y - tilt 
    // ( where tilt make the sequence stand nearer to one of the sides )
    // reversing a part of the sequence you can get all the euclidean rhytms
    void cword ( std::vector<float> & vect, int x, int y, bool upper = true);    
 
    void shift ( std::vector<float> & vect, int shiftAmount);
    // fills all the empty steps with a given value
    void ghost_all ( std::vector<float> & vect, float dynamic );
    
    // each time there is an active step there is chance that it fills the following empty steps
    void ghost_chance ( std::vector<float> & vect, float dynamic, float chance);
     
};

}}}
