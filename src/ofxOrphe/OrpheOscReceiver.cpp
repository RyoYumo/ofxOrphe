//
//  OrpheOscReceiver.cpp
//
//  Created by Ryo Yumoto on 2020/02/11.
//

#include "OrpheOscReceiver.hpp"
#include "ofxPubSubOsc.h"

namespace ofx{
namespace orphe{

OrpheTrackOscReceiver::OrpheTrackOscReceiver() : left_(nullptr), right_(nullptr){
    
}

void OrpheTrackOscReceiver::left(OrpheTrack* left){
    left_ = left;
}

void OrpheTrackOscReceiver::right(OrpheTrack* right){
    right_ = right;
}

void OrpheTrackOscReceiver::subscribe(const int port){
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/motion", [&](ofxOscMessage& m){
        if(!left_) return;
        left_->setOrientation(glm::quat(m.getArgAsFloat(2), m.getArgAsFloat(3), m.getArgAsFloat(4), m.getArgAsFloat(1)));
        left_->setVelocity(glm::vec3(m.getArgAsFloat(5), m.getArgAsFloat(6), m.getArgAsFloat(7)));
        left_->setDisplacement(glm::vec3(m.getArgAsFloat(8), m.getArgAsFloat(9), m.getArgAsFloat(10)));
        left_->setDeltaDisplacement(glm::vec3(m.getArgAsFloat(11), m.getArgAsFloat(12), m.getArgAsFloat(13)));
        left_->setState(m.getArgAsInt(14));
        left_->setCyclePeriod(m.getArgAsInt(15));
        left_->setDetailedCyclePeriod(m.getArgAsInt(16));
        left_->setCycleEvent(m.getArgAsInt(17));
    });
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/swingDuration", [&](ofxOscMessage& m){
        if(!left_) return;
        left_->setSwingDuration(m.getArgAsFloat(1));
    });
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/stanceDuration", [&](ofxOscMessage& m){
        if(!left_) return;
        left_->setStanceDuration(m.getArgAsFloat(1));
    });
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/speed", [&](ofxOscMessage& m){
        if(!left_) return;
        left_->setSpeed(m.getArgAsFloat(1) * 3.6);
    });
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/stride", [&](ofxOscMessage& m){
        if(!left_) return;
        left_->setStrideDistance(m.getArgAsFloat(1));
    });
    
    ofxSubscribeOsc(port, "/LEFT/gaitAnalysis/pronation", [&](ofxOscMessage& m){
        if(!left_) return;
        left_->setPronation(m.getArgAsFloat(1));
    });
    
    // sensor values
    ofxSubscribeOsc(port, "/LEFT/sensorValues", [&](ofxOscMessage& m){
        if(!left_) return;
        left_->setOrientation(glm::vec3(m.getArgAsFloat(4), m.getArgAsFloat(5), m.getArgAsFloat(6)));
        left_->setAcceleration(glm::vec3(m.getArgAsFloat(7), m.getArgAsFloat(8), m.getArgAsFloat(9)));
        left_->setGyro(glm::vec3(m.getArgAsFloat(10), m.getArgAsFloat(11), m.getArgAsFloat(12)));
        left_->setMagnitude(m.getArgAsFloat(13));
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
        if(!right_) return;
        right_->setSwingDuration(m.getArgAsFloat(1));
    });
       
    ofxSubscribeOsc(port, "/RIGHT/gaitAnalysis/stanceDuration", [&](ofxOscMessage& m){
        if(!right_) return;
        right_->setStanceDuration(m.getArgAsFloat(1));
    });
    
    ofxSubscribeOsc(port, "/RIGHT/gaitAnalysis/speed", [&](ofxOscMessage& m){
        if(!right_) return;
        right_->setSpeed(m.getArgAsFloat(1) * 3.6);
    });

    ofxSubscribeOsc(port, "/RIGHT/gaitAnalysis/stride", [&](ofxOscMessage& m){
        if(!right_) return;
        right_->setStrideDistance(m.getArgAsFloat(1));
    });
    
    ofxSubscribeOsc(port, "/RIGHT/gaitAnalysis/pronation", [&](ofxOscMessage& m){
        if(!right_) return;
        right_->setPronation(m.getArgAsFloat(1));
    });
    
    // sensor values
    ofxSubscribeOsc(port, "/RIGHT/sensorValues", [&](ofxOscMessage& m){
        if(!right_) return;
        left_->setOrientation(glm::vec3(m.getArgAsFloat(4), m.getArgAsFloat(5), m.getArgAsFloat(6)));
        left_->setAcceleration(glm::vec3(m.getArgAsFloat(7), m.getArgAsFloat(8), m.getArgAsFloat(9)));
        left_->setGyro(glm::vec3(m.getArgAsFloat(10), m.getArgAsFloat(11), m.getArgAsFloat(12)));
        left_->setMagnitude(m.getArgAsFloat(13));
    });
}

} // namespace orphe
} // namespace ofx
