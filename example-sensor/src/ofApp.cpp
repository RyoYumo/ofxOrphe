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
    l_euler_x_history.setColor(ofColor(226, 100, 100));
    l_euler_y_history.setDrawingArea(ofRectangle(0, 200, 400, 200));
    l_euler_y_history.setInputValueRange(-180, 180);
    l_euler_y_history.setColor(ofColor(76, 104, 191));
    l_euler_z_history.setDrawingArea(ofRectangle(0, 400, 400, 200));
    l_euler_z_history.setInputValueRange(-180, 180);
    l_euler_z_history.setColor(ofColor(76, 204, 130));

    // right
    r_euler_x_history.setDrawingArea(ofRectangle(400, 0, 400, 200));
    r_euler_x_history.setInputValueRange(-90, 90);
    r_euler_x_history.setColor(ofColor(226, 100, 100));
    r_euler_y_history.setDrawingArea(ofRectangle(400, 200, 400, 200));
    r_euler_y_history.setInputValueRange(-180, 180);
    r_euler_y_history.setColor(ofColor(76, 104, 191));
    r_euler_z_history.setDrawingArea(ofRectangle(400, 400, 400, 200));
    r_euler_z_history.setInputValueRange(-180, 180);
    r_euler_z_history.setColor(ofColor(76, 204, 130));

    
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
    ofDrawBitmapStringHighlight("LEFT", 3, 10, ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("RIGHT", 403, 10, ofColor::white, ofColor::black);
    
    ofDrawBitmapStringHighlight("X-AXIS", 3, 30, ofColor::black, ofColor(226, 100, 100));
    ofDrawBitmapStringHighlight("X-AXIS", 403, 30, ofColor::black, ofColor(226, 100, 100));
    
    ofDrawBitmapStringHighlight("Y-AXIS", 3, 220, ofColor::black, ofColor(76, 104, 191));
    ofDrawBitmapStringHighlight("Y-AXIS", 403, 220, ofColor::black, ofColor(76, 104, 191));
    
    ofDrawBitmapStringHighlight("Z-AXIS", 3, 420, ofColor::black, ofColor(76, 204, 130));
    ofDrawBitmapStringHighlight("Z-AXIS", 403, 420, ofColor::black, ofColor(76, 204, 130));
    
    
    l_euler_x_history.draw();
    l_euler_y_history.draw();
    l_euler_z_history.draw();
    r_euler_x_history.draw();
    r_euler_y_history.draw();
    r_euler_z_history.draw();
}
