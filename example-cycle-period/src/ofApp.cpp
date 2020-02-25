#include "ofApp.h"
#include "ofxPubSubOsc.h"
namespace {
constexpr auto kReceivePort = 1111;
constexpr auto kSendPort    = 8888;
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    
    receiver.left(&left);
    receiver.right(&right);
    receiver.subscribe(kReceivePort);
    
    
    l_swing_history.setDrawingArea(ofRectangle(0, 0, 600, 300));
    l_stance_history.setDrawingArea(ofRectangle(0, 0, 600, 300));
    r_swing_history.setDrawingArea(ofRectangle(0, 300, 600, 300));
    r_stance_history.setDrawingArea(ofRectangle(0, 300, 600, 300));
    l_swing_history.setColor(ofColor(110, 146, 161));
    l_stance_history.setColor(ofColor(39, 86, 107));
    r_swing_history.setColor(ofColor(170, 121, 57));
    r_stance_history.setColor(ofColor(255, 219, 170));
    
    left.getCyclePeriodSwingSignal().connect([&](){
        ofxSendOsc("127.0.0.1", kSendPort, "/left/swing");
        l_swing_history.trigger();
    });
    
    left.getCyclePeriodStanceSignal().connect([&](){
        ofxSendOsc("127.0.0.1", kSendPort, "/left/stance");
        l_stance_history.trigger();
    });
    
    right.getCyclePeriodSwingSignal().connect([&](){
        ofxSendOsc("127.0.0.1", kSendPort, "/right/swing");
        r_swing_history.trigger();
    });
    
    right.getCyclePeriodStanceSignal().connect([&](){
        ofxSendOsc("127.0.0.1", kSendPort, "/right/stance");
        r_stance_history.trigger();
    });
    
    ofSetWindowTitle("example-cycle-period");
}

//--------------------------------------------------------------
void ofApp::update(){
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("LEFT", 20, 20);
    ofDrawBitmapString("RIGHT", 20, 320);
    l_swing_history.draw();
    l_stance_history.draw();
    r_swing_history.draw();
    r_stance_history.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

