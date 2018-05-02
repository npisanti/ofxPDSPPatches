ofxPDSPPatches
=====================================

This is a set of high level classes that builds upon [ofxPDSP](https://github.com/npisanti/ofxPDSP).  [ofxWatchFile](https://github.com/nariakiiwatani/ofxWatchFile.git) is also required for some classes to work, but not on Android and iOS. All the classes have a `ofParameterGroup parameters` member that can be easily added to a gui for tweaking things faster in realtime. Some `ofx::patch::sequencer` loads text file in realtime and are updated when the text file changes.

Included `ofx::patch::sequencer`:
- Euclidean : euclidean rhythm generator
- PTracker : file based tracker with probability for each step
- MarkovChain : file based markov chain sequence
- Wolfram : wolfram automata to rhymtm
   
Included `ofx::patch::synth` :
- DataSynth : datasynth class from the data-to-wave example
- GrainDrone : granular sampler with 4 comb resonators
- KarplusStrong : karplus strong string synthesizer
- MultiSampler : from the example-scoring3, good for slicing
- NoiseDevice : clicks and noise burst synthesizer
- QuickSampler : loads a single sample right even from the gui on the fly
- SinePercussion : zaps and beeps percussion
- WaveSynth : wavetable based synthesizer

Included `ofx::patch::effect` :
- BasiVerb : pdsp::BasiVerb wrapper with all the parameters on the gui
- Chorus: pdsp::DimensionChorus with all the parameters on the gui
- Cruncher : bitcrunching and decimation
- Ducker : pdsp::Ducker with all the parameters on the gui
- Filter : multimode filter 
- RingMod : ring modulator
- StereoDelay : L/R delay with different time 

Nicola Pisanti MIT License 2018.


