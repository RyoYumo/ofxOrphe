#pragma once

#include "ofMain.h"
#include "ofxOrphe.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
private:
    ofxOrphe::OrpheTrack left;
    ofxOrphe::OrpheTrack right;
    ofxOrphe::OrpheTrackOscReceiver receiver;
    ofxOrphe::WeightedMovingAverage<float, 10> l_wma_euler_x;
    ofxOrphe::WeightedMovingAverage<float, 10> l_wma_euler_y;
    ofxOrphe::WeightedMovingAverage<float, 10> l_wma_euler_z;
    ofxOrphe::WeightedMovingAverage<float, 10> r_wma_euler_x;
    ofxOrphe::WeightedMovingAverage<float, 10> r_wma_euler_y;
    ofxOrphe::WeightedMovingAverage<float, 10> r_wma_euler_z;
    ofxOrphe::HistoryGraph<float, 50> l_euler_x_history;
    ofxOrphe::HistoryGraph<float, 50> l_euler_y_history;
    ofxOrphe::HistoryGraph<float, 50> l_euler_z_history;
    ofxOrphe::HistoryGraph<float, 50> r_euler_x_history;
    ofxOrphe::HistoryGraph<float, 50> r_euler_y_history;
    ofxOrphe::HistoryGraph<float, 50> r_euler_z_history;
};
