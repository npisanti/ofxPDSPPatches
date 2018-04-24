
#include "PTracker.h"


ofx::patch::sequencer::PTracker::PTracker() {
    
    parameters.setName("ptracker");
    parameters.add( division.set("division", 16, 1, 32) );
    parameters.add( steps.set("steps", 16, 2, 64) );
    parameters.add( start.set("step start", 0, 0, 64) );
        
    parameters.add( autogenerate.set( "autogenerate", true ) );
    parameters.add( repeat.set( "ag counter", 1, 1, 16) );
    parameters.add( regenerate.set( "regenerate", false) );    
    
    bLoaded = false;
    // we already get some memory, for avoid allocating during audio processing
    values.resize( 12 ); // 12 buffer for editing
    for( auto & a : values ){
        a.resize(128);
        for( auto & b : a ){
            b.resize(16);
            for( auto & v : b){
                v = -1.0f;
            }
        }
    }
    //values.clear();
    index = 0;

    code = [&] () noexcept {
        if( autogenerate && (counter() >= repeat) ){ resetCount(); } 
        if( regenerate ){ resetCount(); }
        
        if( regenerate || (autogenerate && counter() == 0) ){

            double length = (double)steps / division;
            int read = index; // memorize the index from which we read, as index can be changed by another thread

            begin( division, length);
                if( !values.empty() && bLoaded ){
                    for( size_t i=start; i<values[read].size() && i<(steps+start); ++i ) {
                        if( values[read][i][0]>=1.0f || pdspChance(values[read][i][0]) ){
                            for( size_t o=1; o<values[read][i].size() && i<(steps+start); ++o ) {
                                if( values[read][i][o] >= 0.0f ) message( (double) (i-start), values[read][i][o], o-1); 
                            }
                        }
                    }
                }
            end();
            
            regenerate = false;
        }
    };
    
}

void ofx::patch::sequencer::PTracker::load( std::string filepath ) {
    path = filepath;
    auto v = ofSplitString(path, "/" );
    string name = v[v.size()-1];
    
    parameters.setName(name);
    pdsp::Sequence::label = name;
#if !defined(OF_TARGET_ANDROID) || !defined(OF_TARGET_IOS)    
    watcher.setCheckIntervalTimef( 0.03f );
    watcher.addListener(this, &PTracker::onFileChange);
	watcher.setTargetPath( filepath );
#else
    loadFile();
#endif
}

void ofx::patch::sequencer::PTracker::loadFile() {
    
	//Load file placed at the given path
	ofFile file( path );
	
	if(!file.exists()){
		ofLogError("The file " + path + " is missing");
        bLoaded = false;
        return;
	}
    
    ofBuffer buffer(file);

    int write = index + 1; // we operate on the next vector of the circular buffer
    if (write>=values.size()){ write=0; }
    int trueLines = 0;

	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        if( line[0] != '#' ){
            trueLines++;
        }
    }
    start.setMax( trueLines-1 );
    
    values[write].resize(trueLines);
    for( auto & a : values[write] ){
        a.resize(64);
        for( auto & val : a ){
            val = -1.0f;
        }
    }

    int i = 0;
	//Read file line by line
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        line += " "; // to be sure that parsing is completed 

        if( line[0] != '#' && line.length()>1 ){
            int o=0;
            string toParse = "";
            bool parsing = false;            

            for( size_t l=0; l<line.length(); ++l ){
                switch( line[l] ){
                    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.': 
                        toParse += (char) line[l];
                        if(!parsing) parsing = true;
                    break;
                    
                    case ',': 
                        toParse += ".";
                        if(!parsing) parsing = true;
                    break;
                    
                    case '-': case 'o': case '~': case '|': 
                        if( o==0){
                            // 100% probability
                            values[write][i][o] = 1.0f;
                        }else{
                            values[write][i][o] = -1.0f;
                        }
                        o++;
                    break;
                    
                    default:
                        if(parsing){
                            values[write][i][o] = ofToFloat( toParse );
                            o++;
                            toParse = "";
                            parsing = false;
                        }
                    break;
                }
            }
            i++;
        }
	}
    
    index = write; // everything done, update the index
    bLoaded = true;
}


