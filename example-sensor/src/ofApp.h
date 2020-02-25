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
    
    // euler
    ofxOrphe::WeightedMovingAverage<glm::vec3, 10> l_wma_euler;
    ofxOrphe::WeightedMovingAverage<glm::vec3, 10> r_wma_euler;
    ofxOrphe::HistoryGraph<float, 50> l_euler_x_history;
    ofxOrphe::HistoryGraph<float, 50> l_euler_y_history;
    ofxOrphe::HistoryGraph<float, 50> l_euler_z_history;
    ofxOrphe::HistoryGraph<float, 50> r_euler_x_history;
    ofxOrphe::HistoryGraph<float, 50> r_euler_y_history;
    ofxOrphe::HistoryGraph<float, 50> r_euler_z_history;
    
    // acc
    ofxOrphe::SimpleMovingAverage<glm::vec3, 10> l_sma_acc;
    ofxOrphe::SimpleMovingAverage<glm::vec3, 10> r_sma_acc;
    ofxOrphe::HistoryGraph<float, 50> l_acc_x_history;
    ofxOrphe::HistoryGraph<float, 50> l_acc_y_history;
    ofxOrphe::HistoryGraph<float, 50> l_acc_z_history;
    ofxOrphe::HistoryGraph<float, 50> r_acc_x_history;
    ofxOrphe::HistoryGraph<float, 50> r_acc_y_history;
    ofxOrphe::HistoryGraph<float, 50> r_acc_z_history;
    
    // gyro
    ofxOrphe::SimpleMovingAverage<glm::vec3, 10> l_sma_gyro;
    ofxOrphe::SimpleMovingAverage<glm::vec3, 10> r_sma_gyro;
    ofxOrphe::SimpleMovingAverage<float, 10> r_sma_gyro_y;
    ofxOrphe::SimpleMovingAverage<float, 10> r_sma_gyro_z;
    ofxOrphe::HistoryGraph<float, 50> l_gyro_x_history;
    ofxOrphe::HistoryGraph<float, 50> l_gyro_y_history;
    ofxOrphe::HistoryGraph<float, 50> l_gyro_z_history;
    ofxOrphe::HistoryGraph<float, 50> r_gyro_x_history;
    ofxOrphe::HistoryGraph<float, 50> r_gyro_y_history;
    ofxOrphe::HistoryGraph<float, 50> r_gyro_z_history;
    
    ofxOrphe::SimpleMovingAverage<float, 10> l_mag;
    ofxOrphe::SimpleMovingAverage<float, 10> r_mag;
    ofxOrphe::HistoryGraph<float, 50> l_mag_history;
    ofxOrphe::HistoryGraph<float, 50> r_mag_history;
};
