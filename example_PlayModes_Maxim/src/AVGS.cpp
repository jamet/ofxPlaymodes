//
//  AVGS.cpp
//  example_PlayModes_Maxim
//
//  Created by Joshua Batty on 17/07/14.
//
//

#include "AVGS.h"

//--------------------------------------------------------------
void AVGS::setup(){

    playModes.setup();
    
    //AUDIO
    sampleRate 	= 44100;
    bufferSize = 512;
    
    grainPlayer.setup();
    mixer.addInputFrom(&grainPlayer);
    
    //SoundStream
    soundStream.listDevices();
	soundStream.setup(this, 2, 2, sampleRate, bufferSize, 4);
	soundStream.setOutput(this);

}

//--------------------------------------------------------------
void AVGS::update(){
    
    grainPlayer.updatePlayHead();
    
    playModes.update();

    playModes.vBuffer.setFramePos((float)grainPlayer.getRecordPostion()); //Here we use the audio record postion to
                                                                        //set the % of the video buffer to write to
    playModes.setSpeed(grainPlayer.speed);
    
    if(grainPlayer.bRecLiveInput==false){
        if(!grainPlayer.bSetPosition==true){
            playModes.setDelay(grainPlayer.ps->getNormalisedPosition());
        }
    }
    else if(grainPlayer.bRecLiveInput==true){
        playModes.setDelay(grainPlayer.ps->getNormalisedPosition());
    }
    

}

//--------------------------------------------------------------
void AVGS::draw(){
    
    ofSetColor(255);
    playModes.draw();
    
    grainPlayer.draw();
    
    playModes.drawData();
}

//--------------------------------------------------------------
void AVGS::audioReceived(float * input, int bufferSize, int nChannels)
{
    grainPlayer.audioReceived(input,bufferSize,nChannels);
}

//--------------------------------------------------------------
void AVGS::audioRequested (float * output, int numFrames, int nChannels)
{
    mixer.audioRequested(output, bufferSize, nChannels);
}

