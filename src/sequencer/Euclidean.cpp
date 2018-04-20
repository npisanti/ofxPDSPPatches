
// Euclidean.cpp
// Nicola Pisanti, MIT License, 2018

#include "Euclidean.h"


ofx::patch::sequencer::Euclidean::Euclidean(){

    //bars.reserve(256);    
    bars.resize(256);
    for(float & value : bars ) value = 0.0f;

    string name = "euclidean sequencer";
    pdsp::Sequence::label = name;
    parameters.setName( name );
    
    parameters.add( this->steps.set( "steps", 16, 1, 64 ));
    parameters.add( this->division.set( "division", 16, 1, 32 ));
    parameters.add( this->x.set( "x", 0.8f, 0.0f, 1.0f ) );
    parameters.add( this->xJit.set( "x jit", 0.2f, 0.0f, 1.0f ) );
    
    parameters.add( this->y.set( "y", 0.2f, 0.0f, 1.0f ) );
    parameters.add( this->yJit.set( "y jit", 0.1f, 0.0f, 1.0f ) );

    parameters.add( this->ghostsChance.set( "ghost chance", 0.0f, 0.0f, 1.0f ) ); 
    parameters.add( this->ghostsDynMin.set( "ghost min dyn", 0.1f, 0.0f, 1.0f) );
    parameters.add( this->ghostsDynMax.set( "ghost max dyn", 0.4f, 0.0f, 1.0f) );
    parameters.add( this->seqShift.set( "shift", 0, -6, 6 ) );
    
    parameters.add( this->automake.set( "automake", false ) );
    parameters.add( this->repeat.set( "am counter", 1, 1, 16) );
    parameters.add( this->remake.set( "remake", true) );    
    
    parameters.add( this->gate.set("gate", 0.5f, 0.0001f, 1.0f ) );
    
    code = [&] () noexcept {
        
        if( automake && (counter() >= repeat) ){ resetCount(); } 
        
        if( remake ){ resetCount(); }
        
        if( remake || (automake && counter() == 0) ){

            double g = gate;    
            
            float xt = x+pdsp::randomBipolar()*xJit;
            float yt = y+pdsp::randomBipolar()*yJit;

            int m = xt * steps;
            int n = yt * steps;
            int clip = steps;
            m = ( m > 0 ) ? m : 0;
            m = ( m < clip ) ? m : clip;
            n = ( n > 1 ) ? n : 1;
            n = ( n < clip ) ? n : clip;
            
            cword( bars, m, n, true);
            
            float gmin = ghostsDynMin;
            float gadd = ghostsDynMax - gmin; 
            ghost_chance( bars, gmin + pdspURan()*gadd, ghostsChance);
            
            shift( bars, seqShift );
            
            double length = (double)steps / division;

            begin( division, length);
                trigVector(bars, g, 0);
            end();
            
            remake = false;
        }
        
    };    
    
}

ofParameterGroup & ofx::patch::sequencer::Euclidean::label( string name ){
    pdsp::Sequence::label = name;
    parameters.setName( name );
    return parameters;
}

   
// ------------------ rhytm generation methods --------------------------------
int ofx::patch::sequencer::Euclidean::gcd( int x, int y ) {
       if( x < y )
          std::swap( x, y );

       while( y > 0 )
       {
          int f = x % y;
          x = y;
          y = f;
       }
       return x;
 }  

void ofx::patch::sequencer::Euclidean::cword ( std::vector<float> & vect, int x, int y, bool upper) {

    // clean vector
    for( float & value : vect ) value = 0.0f;
        
    int max = vect.size();
    
    if ( y > x ) y = x;
    
    
    int div = gcd( y, x );
    
    y = y / div;
    x = x/ div;

    int i = 0;
            
    int a = y;
    int b = x;    
    
    if ( upper ){
        vect[i] = 1.0f;
    }
    i++;
    
    while ( a != b && i < max ){
        if ( a > b ){
            vect[i] = 1.0f;
            b = b + x;
        }else{
            vect[i] = 0.0f;
            a = a + y;
        }
        i++;
    }
    
    if ( i<max ){
        if ( ! upper ){
            vect[i] = 1.0f;
        }
    }
    
    
    for ( int k = 1; k<div; k++){
        
        for (int j = 0; j<i; ++j){
            vect[ j + k*i ] = vect[j];
        }
        
    }
    
}
 

void ofx::patch::sequencer::Euclidean::shift ( std::vector<float> & vect, int shiftAmount) {
    if(shiftAmount!=0){
        if( shiftAmount < 0 ){
            shiftAmount = vect.size() + shiftAmount;
        }
        std::rotate(vect.begin(), vect.begin()+shiftAmount, vect.end());        
    }
}


void ofx::patch::sequencer::Euclidean::ghost_all ( std::vector<float> & vect, float dynamic ) {
    
    for( size_t i=0; i<vect.size(); ++i){
        if( vect[i] == 0.0f ){
            vect[i] = dynamic;
        }
    } 
    
}


void ofx::patch::sequencer::Euclidean::ghost_chance ( std::vector<float> & vect, float dynamic, float chance) {
    
    bool fill;
    if ( vect[0] == 0.0f ){
        fill = pdsp::chance(chance);        
    }else{
        fill = false;
    }

    for( size_t i=0; i<vect.size(); ++i){
        if( vect[i] == 0 ) {
            if ( fill ){
                vect[i] = dynamic;
            }
        }else{
            bool yes = pdsp::chance( chance );
            fill = fill ? false : yes;
        }
    }    
    
}

