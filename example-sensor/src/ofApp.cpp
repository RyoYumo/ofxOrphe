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
    // euler left
    l_euler_x_history.setDrawingArea(ofRectangle(0, 0, 350, 150));
    l_euler_x_history.setInputValueRange(-90, 90);
    l_euler_x_history.setColor(ofColor(226, 100, 100));
    l_euler_y_history.setDrawingArea(ofRectangle(0, 150, 350, 150));
    l_euler_y_history.setInputValueRange(-180, 180);
    l_euler_y_history.setColor(ofColor(76, 104, 191));
    l_euler_z_history.setDrawingArea(ofRectangle(0, 300, 350, 150));
    l_euler_z_history.setInputValueRange(-180, 180);
    l_euler_z_history.setColor(ofColor(76, 204, 130));
    // euler right
    r_euler_x_history.setDrawingArea(ofRectangle(400, 0, 350, 150));
    r_euler_x_history.setInputValueRange(-90, 90);
    r_euler_x_history.setColor(ofColor(226, 100, 100));
    r_euler_y_history.setDrawingArea(ofRectangle(400, 150, 350, 150));
    r_euler_y_history.setInputValueRange(-180, 180);
    r_euler_y_history.setColor(ofColor(76, 104, 191));
    r_euler_z_history.setDrawingArea(ofRectangle(400, 300, 350, 150));
    r_euler_z_history.setInputValueRange(-180, 180);
    r_euler_z_history.setColor(ofColor(76, 204, 130));
    // accel left
    l_acc_x_history.setDrawingArea(ofRectangle(0, 500, 350, 150));
    l_acc_x_history.setInputValueRange(-2.0, 2.0);
    l_acc_x_history.setColor(ofColor(226, 100, 100));
    l_acc_y_history.setDrawingArea(ofRectangle(0, 650, 350, 150));
    l_acc_y_history.setInputValueRange(-2.0, 2.0);
    l_acc_y_history.setColor(ofColor(76, 104, 191));
    l_acc_z_history.setDrawingArea(ofRectangle(0, 800, 350, 150));
    l_acc_z_history.setInputValueRange(-2.0, 2.0);
    l_acc_z_history.setColor(ofColor(76, 204, 130));
     
    // accel right
    r_acc_x_history.setDrawingArea(ofRectangle(400, 500, 350, 150));
    r_acc_x_history.setInputValueRange(-2.0, 2.0);
    r_acc_x_history.setColor(ofColor(226, 100, 100));
    r_acc_y_history.setDrawingArea(ofRectangle(400, 650, 350, 150));
    r_acc_y_history.setInputValueRange(-2.0, 2.0);
    r_acc_y_history.setColor(ofColor(76, 104, 191));
    r_acc_z_history.setDrawingArea(ofRectangle(400, 800, 350, 150));
    r_acc_z_history.setInputValueRange(-2.0, 2.0);
    r_acc_z_history.setColor(ofColor(76, 204, 130));
    // gyro left
    l_gyro_x_history.setDrawingArea(ofRectangle(800, 0, 350, 150));
    l_gyro_x_history.setInputValueRange(-2000, 2000);
    l_gyro_x_history.setColor(ofColor(226, 100, 100));
    l_gyro_y_history.setDrawingArea(ofRectangle(800, 150, 350, 150));
    l_gyro_y_history.setInputValueRange(-2000, 2000);
    l_gyro_y_history.setColor(ofColor(76, 104, 191));
    l_gyro_z_history.setDrawingArea(ofRectangle(800, 300, 350, 150));
    l_gyro_z_history.setInputValueRange(-2000, 2000);
    l_gyro_z_history.setColor(ofColor(76, 204, 130));
    // gyro right
    r_gyro_x_history.setDrawingArea(ofRectangle(1200, 0, 350, 150));
    r_gyro_x_history.setInputValueRange(-2000, 2000);
    r_gyro_x_history.setColor(ofColor(226, 100, 100));
    r_gyro_y_history.setDrawingArea(ofRectangle(1200, 150, 350, 150));
    r_gyro_y_history.setInputValueRange(-2000, 2000);
    r_gyro_y_history.setColor(ofColor(76, 104, 191));
    r_gyro_z_history.setDrawingArea(ofRectangle(1200, 300, 350, 150));
    r_gyro_z_history.setInputValueRange(-2000, 2000);
    r_gyro_z_history.setColor(ofColor(76, 204, 130));
    // mag left
    l_mag_history.setDrawingArea(ofRectangle(800, 500, 350, 150));
    l_mag_history.setInputValueRange(0, 260);
    l_mag_history.setColor(ofColor(226, 100, 100));
    // mag right
    r_mag_history.setDrawingArea(ofRectangle(1200, 500, 350, 150));
    r_mag_history.setInputValueRange(0, 360);
    r_mag_history.setColor(ofColor(226, 100, 100));

    
    left.getOrientationEulerSignal().connect([&](glm::vec3& e){
        glm::vec3 output = l_wma_euler.getOutput(e);
        l_euler_x_history.addValue(output.x);
        l_euler_y_history.addValue(output.y);
        l_euler_z_history.addValue(output.z);
        ofxSendOsc("127.0.0.1", kSendPort, "/left/euler",output);
    });
    
    right.getOrientationEulerSignal().connect([&](glm::vec3& e){
        glm::vec3 output = r_wma_euler.getOutput(e);
        r_euler_x_history.addValue(output.x);
        r_euler_y_history.addValue(output.y);
        r_euler_z_history.addValue(output.z);
        ofxSendOsc("127.0.0.1", kSendPort, "/right/euler",output);
    });
    
    left.getAccelerationSignal().connect([&](glm::vec3& acc){
        glm::vec3 output = l_sma_acc.getOutput(acc);
        l_acc_x_history.addValue(output.x);
        l_acc_y_history.addValue(output.y);
        l_acc_z_history.addValue(output.z);
        ofxSendOsc("127.0.0.1", kSendPort, "/left/acc",output);
    });
    
    right.getAccelerationSignal().connect([&](glm::vec3& acc){
        glm::vec3 output = r_sma_acc.getOutput(acc);
        r_acc_x_history.addValue(output.x);
        r_acc_y_history.addValue(output.y);
        r_acc_z_history.addValue(output.z);
        ofxSendOsc("127.0.0.1", kSendPort, "/right/acc",output);
    });
    
    left.getGyroSignal().connect([&](glm::vec3& gyro){
        glm::vec3 output = l_sma_gyro.getOutput(gyro);
        l_gyro_x_history.addValue(output.x);
        l_gyro_y_history.addValue(output.y);
        l_gyro_z_history.addValue(output.z);
        ofxSendOsc("127.0.0.1", kSendPort, "/left/acc",output);
    });
    
    
    right.getGyroSignal().connect([&](glm::vec3& gyro){
        glm::vec3 output = r_sma_gyro.getOutput(gyro);
        r_gyro_x_history.addValue(output.x);
        r_gyro_y_history.addValue(output.y);
        r_gyro_z_history.addValue(output.z);
        ofxSendOsc("127.0.0.1", kSendPort, "/right/acc",output);
    });
    
    
    
    left.getMagnitudeSignal().connect([&](float& mag){
        float output = l_mag.getOutput(mag);
        l_mag_history.addValue(output);
        ofxSendOsc("127.0.0.1", kSendPort, "/left/mag", output);
    });
    
    right.getMagnitudeSignal().connect([&](float& mag){
        std::cout << mag << std::endl;
        float output = r_mag.getOutput(mag);
        r_mag_history.addValue(output);
        ofxSendOsc("127.0.0.1", kSendPort, "/right/mag", output);
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
    l_acc_x_history.draw();
    l_acc_y_history.draw();
    l_acc_z_history.draw();
    r_acc_x_history.draw();
    r_acc_y_history.draw();
    r_acc_z_history.draw();
    l_gyro_x_history.draw();
    l_gyro_y_history.draw();
    l_gyro_z_history.draw();
    r_gyro_x_history.draw();
    r_gyro_y_history.draw();
    r_gyro_z_history.draw();
    l_mag_history.draw();
    r_mag_history.draw();
    //EULER
     ofDrawBitmapStringHighlight("LEFT", 5, 10, ofColor::white, ofColor::black);
     ofDrawBitmapStringHighlight("RIGHT", 405, 10, ofColor::white, ofColor::black);
     ofDrawBitmapStringHighlight("EULER X-AXIS", 3, 30, ofColor::black, ofColor(226, 100, 100));
     ofDrawBitmapStringHighlight("EULER X-AXIS", 403, 30, ofColor::black, ofColor(226, 100, 100));
     ofDrawBitmapStringHighlight("EULER Y-AXIS", 3, 160, ofColor::black, ofColor(76, 104, 191));
     ofDrawBitmapStringHighlight("EULER Y-AXIS", 403, 160, ofColor::black, ofColor(76, 104, 191));
     ofDrawBitmapStringHighlight("EULER Z-AXIS", 3, 310, ofColor::black, ofColor(76, 204, 130));
     ofDrawBitmapStringHighlight("EULER Z-AXIS", 403, 310, ofColor::black, ofColor(76, 204, 130));
     //ACC
     ofDrawBitmapStringHighlight("LEFT", 5, 515, ofColor::white, ofColor::black);
     ofDrawBitmapStringHighlight("RIGHT", 405, 515, ofColor::white, ofColor::black);
     ofDrawBitmapStringHighlight("ACC X-AXIS", 5, 530, ofColor::black, ofColor(226, 100, 100));
     ofDrawBitmapStringHighlight("ACC X-AXIS", 405, 530, ofColor::black, ofColor(226, 100, 100));
     ofDrawBitmapStringHighlight("ACC Y-AXIS", 5, 660, ofColor::black, ofColor(76, 104, 191));
     ofDrawBitmapStringHighlight("ACC Y-AXIS", 405, 660, ofColor::black, ofColor(76, 104, 191));
     ofDrawBitmapStringHighlight("ACC Z-AXIS", 5, 810, ofColor::black, ofColor(76, 204, 130));
     ofDrawBitmapStringHighlight("ACC Z-AXIS", 405, 810, ofColor::black, ofColor(76, 204, 130));
     //GYRO
     ofDrawBitmapStringHighlight("LEFT", 805, 10, ofColor::white, ofColor::black);
     ofDrawBitmapStringHighlight("RIGHT", 1205, 10, ofColor::white, ofColor::black);
     ofDrawBitmapStringHighlight("GYRO X-AXIS", 805, 30, ofColor::black, ofColor(226, 100, 100));
     ofDrawBitmapStringHighlight("GYRO X-AXIS", 1205, 30, ofColor::black, ofColor(226, 100, 100));
     ofDrawBitmapStringHighlight("GYRO Y-AXIS", 805, 160, ofColor::black, ofColor(76, 104, 191));
     ofDrawBitmapStringHighlight("GYRO Y-AXIS", 1205, 160, ofColor::black, ofColor(76, 104, 191));
     ofDrawBitmapStringHighlight("GYRO Z-AXIS", 805, 310, ofColor::black, ofColor(76, 204, 130));
     ofDrawBitmapStringHighlight("GYRO Z-AXIS", 1205, 310, ofColor::black, ofColor(76, 204, 130));
     //MAG
     ofDrawBitmapStringHighlight("LEFT", 805, 515, ofColor::white, ofColor::black);
     ofDrawBitmapStringHighlight("RIGHT", 1205, 515, ofColor::white, ofColor::black);
     
}
