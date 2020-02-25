#pragma once

#include "ofMain.h"
#include "ofxOrphe.h"
class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
private:
    ofxOrphe::OrpheTrack            left;
    ofxOrphe::OrpheTrack            right;
    ofxOrphe::OrpheTrackOscReceiver receiver;
    ofxOrphe::TriggerGraph<100> l_swing_history;
    ofxOrphe::TriggerGraph<100> l_stance_history;
    ofxOrphe::TriggerGraph<100> r_swing_history;
    ofxOrphe::TriggerGraph<100> r_stance_history;
};
