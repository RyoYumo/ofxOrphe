//
//  OrpheOscReceiver.cpp
//
//  Created by Ryo Yumoto on 2020/02/11.
//

#include "OrpheOscReceiver.hpp"
#include "ofxPubSubOsc.h"

namespace ofx{
namespace orphe{

OrpheOscReceiver::OrpheOscReceiver() : left_(nullptr), right_(nullptr){
    
}

void OrpheOscReceiver::left(OrpheOne* left){
    left_ = left;
}

void OrpheOscReceiver::right(OrpheOne* right){
    right_ = right;
}

void OrpheOscReceiver::subscribe(const int port){
    if(!left_){
        ofxSubscribeOsc(port, "/LEFT/sensorValue", [&](ofxOscMessage& m){
            left_->setOrientationQuat(glm::quat(m.getArgAsFloat(3), // w
                                                m.getArgAsFloat(0), // x
                                                m.getArgAsFloat(1), // y
                                                m.getArgAsFloat(2)));  // z
            left_->setOrientationEuler(glm::vec3(m.getArgAsFloat(4),
                                                 m.getArgAsFloat(5),
                                                 m.getArgAsFloat(6)));
            
            left_->setAccelaration(glm::vec3(m.getArgAsFloat(7),
                                             m.getArgAsFloat(8),
                                             m.getArgAsFloat(9)));
            
            left_->setGyro(glm::vec3(m.getArgAsFloat(10),
                                     m.getArgAsFloat(11),
                                     m.getArgAsFloat(12)));
        });
    }
    
    if(!right_){
        ofxSubscribeOsc(port, "/RIGHT/sensorValue", [&](ofxOscMessage& m){
            right_->setOrientationQuat(glm::quat(m.getArgAsFloat(3), // w
                                                m.getArgAsFloat(0), // x
                                                m.getArgAsFloat(1), // y
                                                m.getArgAsFloat(2)));  // z
            right_->setOrientationEuler(glm::vec3(m.getArgAsFloat(4),
                                                 m.getArgAsFloat(5),
                                                 m.getArgAsFloat(6)));
            
            right_->setAccelaration(glm::vec3(m.getArgAsFloat(7),
                                             m.getArgAsFloat(8),
                                             m.getArgAsFloat(9)));
            
            right_->setGyro(glm::vec3(m.getArgAsFloat(10),
                                     m.getArgAsFloat(11),
                                     m.getArgAsFloat(12)));
        });
    }
}

} // namespace orphe
} // namespace ofx
