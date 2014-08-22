#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
	ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    avgs.setup();

    //GUI
    gui = new ofxUICanvas();
    gui->setFont("GUI/Fett.ttf");
    gui->addLabel("granular synthesis");
    gui->addSpacer();
    
    gui->addSlider("Speed", -1.2, 1.8, &avgs.grainPlayer.speed);
    gui->addSlider("Pitch", 0.0, 10.0, &avgs.grainPlayer.pitch);
    gui->addSlider("GrainSize", 0.025, 0.45, &avgs.grainPlayer.grainSize);
    gui->addSlider("Overlaps", 1, 5, &avgs.grainPlayer.overlaps);
    gui->addSpacer();
    gui->addToggle("Record Input", true);
    gui->addToggle("Set Position", &avgs.grainPlayer.bSetPosition);
    gui->addSlider("Position", 0.0, 1.0, 1.0);
 //   gui->addSlider("Loop Size", 0.0 ,1.0, 0.0);
    gui->addSlider("Volume", 0.0, 1.0, &avgs.grainPlayer.volume);
    
    
    gui->autoSizeToFitWidgets();
    
    gui->loadSettings("GUI/guiSettings.xml");
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    avgs.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    
    avgs.draw();
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels)
{
    avgs.audioReceived(input,bufferSize,nChannels);
}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels)
{
    avgs.audioRequested(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
	int kind = e.widget->getKind();
	
    if(name == "Position")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		avgs.grainPlayer.playHead = slider->getScaledValue();        
        avgs.playModes.setDelay(slider->getScaledValue());
	}
    else if(name == "Loop Size")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		avgs.grainPlayer.loopSize = slider->getScaledValue();
	}
    else if(name == "Record Input"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        avgs.grainPlayer.bRecLiveInput = toggle->getValue();
        if(toggle->getValue()==true){
            avgs.playModes.bRecord = true;
        } else {
            avgs.playModes.bRecord = false;
        }
    }
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
