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
    ofxOrphe::HistoryGraph<float, 50> l_speed_history;
    ofxOrphe::HistoryGraph<float, 50> r_speed_history;
};
