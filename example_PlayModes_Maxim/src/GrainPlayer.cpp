//
//  GrainPlayer.cpp
//  testCpp11
//
//  Created by Joshua Batty on 4/06/14.
//
//

#include "GrainPlayer.h"

//--------------------------------------------------------------
void GrainPlayer::setSampleRate( int rate )
{
	sampleRate = rate;
}

//--------------------------------------------------------------
void GrainPlayer::setup(){
    
    //Drawing
    prevXpos = prevYpos = 0;
    curXpos = curYpos = 0;

    //Recording
    recordPosition = 0;
    bSetPosition = false;
    bRecLiveInput = true;
    bUpdatePlayheadEvent = false;
    recMix = 0.0;
    
    //Granular
    speed = 1.0;//0.98; // Put the play position just a tad behind the record position to prevent clicking
    grainSize = 0.25;
    pitch = 1.0;
    playHead = 0.0;
    overlaps = 3;
    
    volume = 0.05;
    sampleRate 	= 44100;
    bufferSize = 512;
    
    //Maxi
    samp.load(ofToDataPath("400Frames(60fps).wav"));
    ps = new maxiPitchStretch<grainPlayerWin>(&samp);
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
}

//--------------------------------------------------------------
void GrainPlayer::updatePlayHead(){
    if(!bSetPosition) {
        if(bUpdatePlayheadEvent==true){
            ps->setPosition(ofMap(samp.recordPosition,0,LENGTH,0.0,1.0));
        }
        bUpdatePlayheadEvent = false;
    } else {
        bUpdatePlayheadEvent = true;
    }
    
    if(ofGetFrameNum()==100){
        speed = 1.0;
    }
}


//--------------------------------------------------------------
void GrainPlayer::draw(){
    drawWaveform();
}

//--------------------------------------------------------------
void GrainPlayer::audioReceived(float * input, int bufferSize, int nChannels)
{
    for (int i = 0; i < bufferSize; i++)
    {
        samp.loopRecord(input[i*nChannels], bRecLiveInput, recMix);
        recordPosition = samp.recordPosition / (double)(LENGTH);
    }
}

//--------------------------------------------------------------
void GrainPlayer::audioRequested (float * output, int numFrames, int nChannels)
{
 
    for (int i = 0; i < bufferSize; i++)
    {
        //Play the Granular Synth play method
        if(bSetPosition == true){
            ps->setPosition(playHead);
        }
        wave = ps->play(pitch, speed, grainSize, (int)overlaps);
        
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0] * volume;
        output[i*nChannels + 1] = outputs[1] * volume;
    }
}

//--------------------------------------------------------------
float GrainPlayer::getRecordPostion(){
    return recordPosition;
}

//--------------------------------------------------------------
void GrainPlayer::drawWaveform(){
    ofSetColor(255);
    ofFill();
    
    const float waveformWidth  = ofGetWidth() - 40;
    const float waveformHeight = 300;
    
    float top = ofGetHeight() - waveformHeight - 20;
    float left = 20;
    
    // draw the audio waveform
    for(int i= 0; i < LENGTH; i+=bufferSize){
        curXpos = ofMap(i,0,LENGTH,left,waveformWidth);
        curYpos = ofMap(samp.temp[i],-32768,32768,top,waveformHeight+top);
        ofEllipse(curXpos, curYpos, 2, 2);
        ofLine(curXpos, curYpos, prevXpos, prevYpos);
        if(i < LENGTH-bufferSize){
            prevXpos = curXpos;
            prevYpos = curYpos;
        } else {
            prevXpos = left;
            prevYpos = waveformHeight+top;
        }
    }
    
    // draw a playhead over the waveform
    ofSetColor(ofColor::white);
    ofLine(left + ps->getNormalisedPosition() * waveformWidth, top, left + ps->getNormalisedPosition() * waveformWidth, top + waveformHeight);
    ofDrawBitmapString("PlayHead", left + ps->getNormalisedPosition() * waveformWidth-69, top+30);

    // Draw Current Recording Position
    ofSetColor(ofColor::red);
    ofLine(left + getRecordPostion() * waveformWidth, top, left + getRecordPostion() * waveformWidth, top + waveformHeight);
    ofDrawBitmapString("RecPos", left + getRecordPostion() * waveformWidth-52, top+15);

    // draw a frame around the whole thing
    ofSetColor(ofColor::white);
    ofNoFill();
    ofRect(left, top, waveformWidth, waveformHeight);
}

