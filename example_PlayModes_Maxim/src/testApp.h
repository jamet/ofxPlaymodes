#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "PlayModes.h"
#include "GrainPlayer.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        PlayModes playModes;
        GrainPlayer grainPlayer;
		
        //AUDIO
        void audioIn(float * input, int bufferSize, int nChannels);
        void audioOut(float * output, int bufferSize, int nChannels);
        
        int sampleRate;
        int bufferSize;
        ofSoundStream soundStream;
        ofSoundMixer mixer;
    
        //GUI
        ofxUICanvas *gui;
        void guiEvent(ofxUIEventArgs &e);
};
