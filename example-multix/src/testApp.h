#ifndef _TEST_APP
#define _TEST_APP



#include "ofMain.h"
#include "ofxPlaymodes.h"


class testApp : public ofBaseApp{

public:

    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

	

    VideoGrabber videoInput;

    VideoBuffer * videoBuffer;

    float vFPS;
    float appFPS;
    int updateStats;

    char msg[1024];

    int background;

    bool drawStats;
    
	MultixRenderer * multix;
};

	
#endif
