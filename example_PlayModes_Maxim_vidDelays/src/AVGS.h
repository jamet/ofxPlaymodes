//
//  AVGS.h
//  example_PlayModes_Maxim
//
//  Created by Joshua Batty on 17/07/14.
//
//

#pragma once

#include "ofMain.h"
#include "PlayModes.h"
#include "GrainPlayer.h"

class AVGS : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    PlayModes playModes;
    GrainPlayer grainPlayer;
    
    //AUDIO
    void audioReceived(float * input, int bufferSize, int nChannels);
    void audioRequested (float * output, int numFrames, int nChannels);
    
    int sampleRate;
    int bufferSize;
    ofSoundStream soundStream;
    ofSoundMixer mixer;
    

};
