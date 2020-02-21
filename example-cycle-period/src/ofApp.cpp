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
    
    
    left_swing_history.setArea(ofRectangle(0, 0, 600, 300));
    left_stance_history.setArea(ofRectangle(0, 0, 600, 300));
    right_swing_history.setArea(ofRectangle(0, 300, 600, 300));
    right_stance_history.setArea(ofRectangle(0, 300, 600, 300));
    
    left_swing_history.setColor(ofColor(110, 146, 161));
    left_stance_history.setColor(ofColor(39, 86, 107));
    right_swing_history.setColor(ofColor(170, 121, 57));
    right_stance_history.setColor(ofColor(255, 219, 170));
    
    
    swing_duration_diff_hisotry.setArea(ofRectangle(600, 0, 600, 300));
    swing_duration_diff_hisotry.setInputValueRange(-0.5, 0.5);
    
    stance_duration_diff_hisotry.setArea(ofRectangle(600, 300, 600, 300));
    stance_duration_diff_hisotry.setInputValueRange(-0.5, 0.5);
    
    left.getCyclePeriodSwingSignal().connect([&](){
        ofxSendOsc("127.0.0.1", kSendPort, "/left/swing");
        left_swing_history.trigger();
    });
    
    left.getCyclePeriodStanceSignal().connect([&](){
        ofxSendOsc("127.0.0.1", kSendPort, "/left/stance");
        left_stance_history.trigger();
    });
    
    right.getCyclePeriodSwingSignal().connect([&](){
        ofxSendOsc("127.0.0.1", kSendPort, "/right/swing");
        right_swing_history.trigger();
    });
    
    right.getCyclePeriodStanceSignal().connect([&](){
        ofxSendOsc("127.0.0.1", kSendPort, "/right/stance");
        right_stance_history.trigger();
    });
    
    
    right.getSwingDurationSignal().connect([&](float& val){
        swing_duration_diff_hisotry.value(left.getSwingDuration() - val);
    });
    
    right.getStanceDurationSignal().connect([&](float& val){
        stance_duration_diff_hisotry.value(left.getStanceDuration() - val);
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
    
    ofDrawBitmapString("Swing duration difference", 620, 20);
    ofDrawBitmapString("LEFT - RIGHT = " + ofToString(swing_duration_diff_hisotry.getValue()), 620, 40);

    ofDrawBitmapString("Stance duration difference", 620, 320);
    ofDrawBitmapString("LEFT - RIGHT = " + ofToString(stance_duration_diff_hisotry.getValue()), 620, 340);
    
    left_swing_history.draw();
    left_stance_history.draw();
    right_swing_history.draw();
    right_stance_history.draw();
    swing_duration_diff_hisotry.draw();
    stance_duration_diff_hisotry.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

