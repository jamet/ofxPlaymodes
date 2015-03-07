/*
 * AudioFrame.h
 *
 *  Created on: 09-oct-2008
 *      Author: arturo castro
 */


#ifndef VIDEOGRABBER_H_INCLUDED
#define VIDEOGRABBER_H_INCLUDED

#include "VideoSource.h"
#include "ofMain.h"


namespace ofxPm{
class VideoGrabber: public VideoSource, public ofVideoGrabber{
public:
    VideoGrabber();
    virtual ~VideoGrabber();

    bool initGrabber(int w, int h);

	VideoFrame getNextVideoFrame();
    float getFps();
	// ugly! need to be able to override the fps of the grabber. ofVideoGrabber doesn't have a getFps !!
	void setFps(float fps);

    void update();

    bool setPixelFormat(ofPixelFormat pixelFormat);

    ofPixelFormat 		getPixelFormat() ;

    ofPixels& 			getPixels();
		//const ofPixels&		getPixels() const;
		void				setDeviceID(int _deviceID);
		ofTexture &			getTexture();
		//const ofTexture &	getTexture() const;
		OF_DEPRECATED_MSG("Use getTexture",ofTexture &			getTextureReference());
		//OF_DEPRECATED_MSG("Use getTexture",const ofTexture &	getTextureReference() const);

    float				getHeight() ;
	float				getWidth() ;



private:
    void newFrame(ofPixels & frame);
	float fps;
	VideoFrame frame;
};
}

#endif // VIDEOGRABBER_H_INCLUDED
