#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
	ofEnableAlphaBlending();
    
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

    //GUI
    gui = new ofxUICanvas();
    gui->setFont("GUI/Fett.ttf");
    gui->addLabel("granular synthesis");
    gui->addSpacer();
    
    gui->addSlider("Speed", -4.0, 4.0, &grainPlayer.speed);
    gui->addSlider("Pitch", 0.0, 10.0, &grainPlayer.pitch);
    gui->addSlider("GrainSize", 0.025, 0.45, &grainPlayer.grainSize);
    gui->addSlider("Overlaps", 1, 5, &grainPlayer.overlaps);
    gui->addSpacer();
    gui->addToggle("Record Input", true);
    gui->addToggle("Set Position", &grainPlayer.bSetPosition);
    gui->addSlider("Position", 0.0, 1.0, 0.0);
    gui->addSlider("RecMix", 0.0, 1.0, &grainPlayer.recMix);
    gui->addSlider("Volume", 0.0, 1.0, &grainPlayer.volume);
    
    
    gui->autoSizeToFitWidgets();
    
    gui->loadSettings("GUI/guiSettings.xml");
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
}

//--------------------------------------------------------------
void testApp::update(){
    playModes.update();
    grainPlayer.updatePlayHead();
    
    if(grainPlayer.bRecLiveInput==false){
        if(!grainPlayer.bSetPosition==true){
            playModes.setDelay(grainPlayer.ps->getNormalisedPosition());
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255);
    playModes.draw();
    
    grainPlayer.draw();
    
    playModes.drawData();
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels)
{
    grainPlayer.audioReceived(input,bufferSize,nChannels);
}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels)
{
    mixer.audioRequested(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
	int kind = e.widget->getKind();
	
    if(name == "Position")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		grainPlayer.playHead = slider->getScaledValue();
        playModes.setDelay(slider->getScaledValue());
	}
    else if(name == "Record Input"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        grainPlayer.bRecLiveInput = toggle->getValue();
        if(toggle->getValue()==true){
            //playModes.vHeader.setInPct(grainPlayer.getRecordPostion());
            playModes.vBuffer.resume();
        } else {
            playModes.vBuffer.stop();
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
