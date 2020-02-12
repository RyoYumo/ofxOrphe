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

void OrpheOscReceiver::left(OrpheTrack* left){
    left_ = left;
}

void OrpheOscReceiver::right(OrpheTrack* right){
    right_ = right;
}

void OrpheOscReceiver::subscribe(const int port){
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/motion", [&](ofxOscMessage& m){
        if(!left_) return;
        left_->setOrientation(glm::quat(m.getArgAsFloat(2), m.getArgAsFloat(3), m.getArgAsFloat(4), m.getArgAsFloat(1)));
        left_->setVelocity(glm::vec3(m.getArgAsFloat(5), m.getArgAsFloat(6), m.getArgAsFloat(7)));
        left_->setDisplacement(glm::vec3(m.getArgAsFloat(8), m.getArgAsFloat(9), m.getArgAsFloat(10)));
        left_->setDeltaDisplacement(glm::vec3(m.getArgAsFloat(11), m.getArgAsFloat(12), m.getArgAsFloat(13)));
        left_->setState(14);
        left_->setCyclePeriod(m.getArgAsInt(15));
        left_->setDetailedCyclePeriod(m.getArgAsInt(16));
        left_->setCycleEvent(m.getArgAsInt(17));
    });
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/swingDuration", [&](ofxOscMessage& m){
        left_->setSwingDuration(m.getArgAsFloat(1));
    });
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/stanceDuration", [&](ofxOscMessage& m){
        left_->setStanceDuration(m.getArgAsFloat(1));
    });
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/speed", [&](ofxOscMessage& m){
        left_->setSpeed(m.getArgAsFloat(1) * 3.6);
    });
    
    ofxSubscribeOsc(port, "/RIGHT/gaitAnalysis/motion", [&](ofxOscMessage& m){
        if(!right_) return;
        right_->setOrientation(glm::quat(m.getArgAsFloat(2), m.getArgAsFloat(3), m.getArgAsFloat(4), m.getArgAsFloat(1)));
        right_->setVelocity(glm::vec3(m.getArgAsFloat(5), m.getArgAsFloat(6), m.getArgAsFloat(7)));
        right_->setDisplacement(glm::vec3(m.getArgAsFloat(8), m.getArgAsFloat(9), m.getArgAsFloat(10)));
        right_->setDeltaDisplacement(glm::vec3(m.getArgAsFloat(11), m.getArgAsFloat(12), m.getArgAsFloat(13)));
        right_->setState(14);
        right_->setCyclePeriod(m.getArgAsInt(15));
        right_->setDetailedCyclePeriod(m.getArgAsInt(16));
        right_->setCycleEvent(m.getArgAsInt(17));
    });
    
    ofxSubscribeOsc(port, "/RIGHT/gaitAnalysis/swingDuration", [&](ofxOscMessage& m){
        right_->setSwingDuration(m.getArgAsFloat(1));
    });
       
    ofxSubscribeOsc(port, "/RIGHT/gaitAnalysis/stanceDuration", [&](ofxOscMessage& m){
        right_->setStanceDuration(m.getArgAsFloat(1));
    });
    
    ofxSubscribeOsc(port, "/RIGHT/gaitAnalysis/speed", [&](ofxOscMessage& m){
        right_->setSpeed(m.getArgAsFloat(1) * 3.6);
    });

    
}

} // namespace orphe
} // namespace ofx
