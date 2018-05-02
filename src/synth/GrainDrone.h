
#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "../util/SampleControl.h"

namespace ofx { namespace patch { namespace synth {

class GrainDrone {
    
public:
    void resize( int w, int h );
    ofParameterGroup & setup( int w, int h, std::string name="graindrone", bool guicontrol=true );
    void draw( int x, int y) ;

    void addSample( util::SampleControl & sample );

    pdsp::Patchable& in_dry_control();
    pdsp::Patchable& in_resonator_control( int i );
    pdsp::Patchable& in_position();
    pdsp::Patchable& in_fb();
    pdsp::Patchable& out_L();
    pdsp::Patchable& out_R();
    
    float meter_cutoff() const;
        
    pdsp::GrainCloud        cloud;  
    ofParameterGroup        parameters;

    std::vector<ofxPDSPValue>    resonators_control;    
    ofxPDSPValue            dry_control;
    ofxPDSPValue            positionControl;
    ofxPDSPValue            densityControl;
    ofxPDSPValue            fader;        
    ofxPDSPValue            resonatorsFBControl;
    
    void smoothing( float ms );
   
    ofParameterGroup & label( std::string name );
    
private:

    std::vector<pdsp::PatchNode> sendnode;
    pdsp::PatchNode              drynode;

    std::vector<util::SampleControl*> samples;

    pdsp::DBtoLin       dBtoLin;
    
    pdsp::PatchNode     fbInput;

    ofxPDSPValue        positionJitterControl;
    ofxPDSPValue        lengthControl;

    ofxPDSPValue        distanceJitterControl;
    ofxPDSPValue        pitchJitterControl;
    ofxPDSPValue        selectSampleControl;
    
    ofxPDSPValue        pitchControl;
    
    ofxPDSPValue            resonatorsPitchMaster;
    std::vector<ofxPDSPValue>    resonatorsPitchControls;

    ofxPDSPValue            resonatorsLRSpreadControl;

    ofxPDSPValue            resonatorsDampControl;
   
    int                     grainVoices;

    std::vector<pdsp::CombFilter> resonators;
    std::vector<pdsp::Amp>        resonators_sends;

    pdsp::Amp               dryL;
    pdsp::Amp               dryR;

    pdsp::Amp               voiceAmpL;
    pdsp::Amp               voiceAmpR;
    
    pdsp::LFOPhazor         lfoPhazor;
    pdsp::CheapTri          lfo;
    pdsp::Amp               pitchModAmt;
    ofxPDSPValue            pitchModControl;
    ofxPDSPValue            pitchModSpeed;

    bool showLabel;

    int uiWidth;
    int uiHeight;
  
    int grainW;
    int grainH;
    
};

}}} // end namespaces