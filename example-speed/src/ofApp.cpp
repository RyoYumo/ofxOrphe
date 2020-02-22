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
    
    left_speed_hisotry.setArea(ofRectangle(0, 0, 600, 300));
    left_speed_hisotry.setInputValueRange(0, 15);
    
    right_speed_hisotry.setArea(ofRectangle(0, 300, 600, 300));
    right_speed_hisotry.setInputValueRange(0, 15);
    
    left.getSpeedSignal().connect([&](float& speed){
        left_speed_hisotry.value(speed);
        ofxSendOsc("127.0.0.1", kSendPort, "/left/speed", speed);
    });
    
    right.getSpeedSignal().connect([&](float& speed){
        right_speed_hisotry.value(speed);
        ofxSendOsc("127.0.0.1", kSendPort, "/right/speed", speed);
    });
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("LEFT", 20, 20);
    ofDrawBitmapString(ofToString(left_speed_hisotry.getValue()), 20, 40);
    ofDrawBitmapString("RIGHT", 20, 320);
    ofDrawBitmapString(ofToString(right_speed_hisotry.getValue()), 20, 340);
    left_speed_hisotry.draw();
    right_speed_hisotry.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
