#include "ofApp.h"
#include "ofxPubSubOsc.h"

namespace {
constexpr auto kSendPort = 8888;
constexpr auto kReceivePort = 1111;
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    receiver.left(&left);
    receiver.right(&right);
    receiver.subscribe(kReceivePort);
    
    // left
    l_euler_x_history.setDrawingArea(ofRectangle(0, 0, 400, 200));
    l_euler_x_history.setInputValueRange(-90, 90);
    l_euler_x_history.setColor(ofColor::lightPink);
    l_euler_y_history.setDrawingArea(ofRectangle(0, 200, 400, 200));
    l_euler_y_history.setInputValueRange(-180, 180);
    l_euler_y_history.setColor(ofColor::royalBlue);
    l_euler_z_history.setDrawingArea(ofRectangle(0, 400, 400, 200));
    l_euler_z_history.setInputValueRange(-180, 180);
    l_euler_z_history.setColor(ofColor::yellowGreen);

    // right
    r_euler_x_history.setDrawingArea(ofRectangle(400, 0, 400, 200));
    r_euler_x_history.setInputValueRange(-90, 90);
    r_euler_x_history.setColor(ofColor::lightPink);
    r_euler_y_history.setDrawingArea(ofRectangle(400, 200, 400, 200));
    r_euler_y_history.setInputValueRange(-180, 180);
    r_euler_y_history.setColor(ofColor::royalBlue);
    r_euler_z_history.setDrawingArea(ofRectangle(400, 400, 400, 200));
    r_euler_z_history.setInputValueRange(-180, 180);
    r_euler_z_history.setColor(ofColor::yellowGreen);

    
    left.getOrientationEulerSignal().connect([&](glm::vec3& e){
        glm::vec3 output = glm::vec3{ l_wma_euler_x.getOutput(e.x),
                                      l_wma_euler_y.getOutput(e.y),
                                      l_wma_euler_z.getOutput(e.z) };
        l_euler_x_history.addValue(output.x);
        l_euler_y_history.addValue(output.y);
        l_euler_z_history.addValue(output.z);
        ofxSendOsc("127.0.0.1", kSendPort, "/left/euler",output);
    });
    
    right.getOrientationEulerSignal().connect([&](glm::vec3& e){
        glm::vec3 output = glm::vec3{ r_wma_euler_x.getOutput(e.x),
                                      r_wma_euler_y.getOutput(e.y),
                                      r_wma_euler_z.getOutput(e.z) };
        r_euler_x_history.addValue(output.x);
        r_euler_y_history.addValue(output.y);
        r_euler_z_history.addValue(output.z);
        ofxSendOsc("127.0.0.1", kSendPort, "/right/euler",output);
    });

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    l_euler_x_history.draw();
    l_euler_y_history.draw();
    l_euler_z_history.draw();
    r_euler_x_history.draw();
    r_euler_y_history.draw();
    r_euler_z_history.draw();
}