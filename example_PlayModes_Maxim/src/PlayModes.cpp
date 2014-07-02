//
//  PlayModes.cpp
// 
//
//  Created by Joshua Batty on 5/05/14.
//
//

#include "PlayModes.h"
using namespace ofxPm;

//--------------------------------------------------------------
void PlayModes::setup(){

    bRecord = true;
    bRecordSwitch = true;
    
    fps = 60;
    delay = 0;
    
	vGrabber.initGrabber(640,480);

	vRate.setup(vGrabber,fps);
	vBuffer.setup(vRate,NUM_FRAMES,true);
	vHeader.setup(vBuffer);
	vHeader.setDelayMs(0);
	vRenderer.setup(vHeader);

}


void PlayModes::setFps(int _fps){
    vRate.setFps(_fps);
    vHeader.setFps(_fps);
}

void PlayModes::setDelay(float _delay){
    //vBuffer.setFramePos(ofMap(_delay, 0.0, 1.0, 0, NUM_FRAMES));

    delay = ofMap(_delay, 1.0, 0.0, 0, NUM_FRAMES);
    vHeader.setDelayFrames(delay);
}

//--------------------------------------------------------------
void PlayModes::recordingStatus(){
    if(bRecord) {
        if(bRecordSwitch==true){
            vBuffer.resume();
            cout << "RESUME CUNTNESS" << endl;
        }
        bRecordSwitch = false;
    } else if(bRecord==false){
        if(bRecordSwitch==false){
            vBuffer.stop();
            cout << "HALT DA CUNT" << endl;
        }
        bRecordSwitch = true;
    }
}

//--------------------------------------------------------------
void PlayModes::update(){
    recordingStatus();
	vGrabber.update();
    vRate.glThreadUpdate();

 
}

//--------------------------------------------------------------
void PlayModes::draw(){
    
	vBuffer.draw();
	vHeader.draw();
    
	vRenderer.draw(0,0,ofGetWidth(),ofGetHeight());
    
	//gui.draw();
	ofDrawBitmapString("FPS: " + ofToString(int(ofGetFrameRate()))
                       + " || cameraBuffer FPS " + ofToString(vBuffer.getRealFPS())
                       + " || videoframes pool size: " + ofToString(VideoFrame::getPoolSize(VideoFormat(640,480,3)))
                       + " || total frames: " +ofToString(VideoFrame::getTotalNumFrames()),20,ofGetHeight()-40);
    
}

//--------------------------------------------------------------
void PlayModes::drawData(){
    float vhPos = ofMap(vHeader.getDelayFrames(),0,NUM_FRAMES,0.0,1.0);

    
    const float waveformWidth  = ofGetWidth() - 40;
    const float waveformHeight = 300;
    
    float top = ofGetHeight() - waveformHeight - 20;
    float left = 20;
    
    ////////// Video Header Play Pos ///////////////////////
    ofSetColor(255,0,0);
    ofDrawBitmapString("Video Header Play Pos", left, top-10);
  //  ofLine(left, top, waveformWidth, top);
    
    // frame pos
    ofSetColor(0,0,255);
    float framePosPerc = (float)vBuffer.getFramePos() / (float)NUM_FRAMES;
    ofLine(left+ (framePosPerc * (waveformWidth-left)), top, left+ (framePosPerc * (waveformWidth-left)), top+waveformHeight);
    ofDrawBitmapString("FramePos", left + framePosPerc * waveformWidth-76, top+45);

    ofCircle(left+(framePosPerc*(waveformWidth-left)), top, 10);
}

