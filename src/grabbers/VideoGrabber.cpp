/*
 * AudioFrame.h
 *
 *  Created on: 09-oct-2008
 *      Author: arturo castro
 */

#include "VideoGrabber.h"

namespace ofxPm{
VideoGrabber::VideoGrabber(){
}

VideoGrabber::~VideoGrabber(){
}

bool VideoGrabber::initGrabber(int w, int h){
	bool ret = ofVideoGrabber::initGrabber(w,h,false);
	//bool ret = ofGstVideoGrabber::setup(w, h);
	//frame = VideoFrame::newVideoFrame(getPixelsRef());
    frame = VideoFrame::newVideoFrame(getPixels());

	return ret;
}

VideoFrame VideoGrabber::getNextVideoFrame(){
    return frame;
}

void VideoGrabber::update(){
	ofVideoGrabber::update();
	if(isFrameNew()){
		newFrame(getPixels());
	}
}

void VideoGrabber::newFrame(ofPixels & pixels){
	frame = VideoFrame::newVideoFrame(pixels);
	frame.getTextureRef();
	newFrameEvent.notify(this,frame);
}

//------------------------------------------------------
float VideoGrabber::getFps(){
	return fps;
}

//------------------------------------------------------
void VideoGrabber::setFps(float fps){
	this->fps = fps;
}

bool	VideoGrabber::setPixelFormat(ofPixelFormat pixelFormat){
    return ofVideoGrabber::setPixelFormat(pixelFormat);
}
	;

ofPixelFormat VideoGrabber::getPixelFormat() {
    return ofVideoGrabber::getPixelFormat();
}

ofPixels&      VideoGrabber::getPixels(){
    return ofVideoGrabber::getPixels();
}

void VideoGrabber::setDeviceID(int _deviceID){
     ofVideoGrabber::setDeviceID( _deviceID);
}

ofTexture &	VideoGrabber::getTexture(){
    return ofVideoGrabber::getTexture();
}

float VideoGrabber::getHeight() {
    return ofVideoGrabber::getHeight();
}

float VideoGrabber::getWidth() {
    return ofVideoGrabber::getWidth();
}



}
