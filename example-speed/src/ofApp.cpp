#include "ofApp.h"
#include "ofxPubSubOsc.h"

namespace {
constexpr auto kReceivePort = 2222;
constexpr auto kSendPort    = 8888;
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    receiver.left(&left);
    receiver.right(&right);
    receiver.subscribe(kReceivePort);
    
    l_speed_history.setDrawingArea(ofRectangle(0, 0, 600, 300));
    l_speed_history.setInputValueRange(0, 15);
    
    r_speed_history.setDrawingArea(ofRectangle(0, 300, 600, 300));
    r_speed_history.setInputValueRange(0, 15);
    
    left.getSpeedSignal().connect([&](float& speed){
        l_speed_history.addValue(speed);
        ofxSendOsc("127.0.0.1", kSendPort, "/left/speed", speed);
    });
    
    right.getSpeedSignal().connect([&](float& speed){
        r_speed_history.addValue(speed);
        ofxSendOsc("127.0.0.1", kSendPort, "/right/speed", speed);
    });
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("LEFT", 20, 20);
    ofDrawBitmapString(ofToString(l_speed_history.getValue()), 20, 40);
    ofDrawBitmapString("RIGHT", 20, 320);
    ofDrawBitmapString(ofToString(r_speed_history.getValue()), 20, 340);
    l_speed_history.draw();
    r_speed_history.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
