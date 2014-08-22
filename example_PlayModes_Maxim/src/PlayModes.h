//
//  PlayModes.h
//  
//
//  Created by Joshua Batty on 5/05/14.
//
//

#pragma once

#include "ofMain.h"
#include "VideoBuffer.h"
#include "VideoHeader.h"
#include "VideoGrabber.h"
#include "VideoRenderer.h"
#include "VideoRate.h"
#include "BasicVideoRenderer.h"
#include "VideoMixerGPU.h"


#define NUM_FRAMES 400

class PlayModes{
    
public:
    void setup();
    void update();
    void draw();
    void drawData();
    
    void recordingStatus();
    
    void setFps(int _fps);
    void setDelay(float _delay);
    void setSpeed(float _speed);

    ofxPm::VideoGrabber vGrabber;
    ofxPm::VideoBuffer vBuffer;
    ofxPm::VideoHeader vHeader;
    ofxPm::BasicVideoRenderer vRenderer;
    ofxPm::VideoRate vRate;
    ofxPm::VideoMixerGPU vMixer;

    int fps;
    int delay;

    bool bRecord;
    bool bRecordSwitch;
    
    float framePosPerc;

};
