//
//  TriggerGraph.hpp
//  example-cycle-period
//
//  Created by Ryo Yumoto on 2020/02/24.
//

#ifndef OFX_ORPHE_UTILITY_TRIGGERGRAPH_HPP_
#define OFX_ORPHE_UTILITY_TRIGGERGRAPH_HPP_

#include "ofMain.h"

namespace ofx{
namespace orphe {
template<std::size_t BufferSize>
class TriggerGraph {
public:
    static constexpr auto size = BufferSize;
    TriggerGraph(): buffer_(size), area_(0, 0, 600, 300),color_(ofColor::white){
        ofAddListener(ofEvents().update, this, &TriggerGraph::update);
    }
    
    void setDrawingArea(const ofRectangle& area){ area_ = area;}
    void setColor(const ofColor& color){ color_ = color;}
    void trigger(){ buffer_.back() = 1;}
    void draw(){
        ofPushStyle();
        ofNoFill();
        ofDrawRectangle(area_);
        ofPopStyle();

        ofPushStyle();
        ofSetColor(color_);
        ofPushMatrix();
        ofTranslate(area_.x, area_.y + area_.height);
        ofBeginShape();
        for(auto i = 0; i < buffer_.size(); ++i){
            if(i == 0) ofVertex(0, 0);
            auto x = i * ((float)area_.width / (buffer_.size()-1));
            auto y = buffer_[i] == 1 ? area_.height * -0.8 : 0.0;
            ofVertex(x,y);
            if(i == buffer_.size() -1) ofVertex(area_.width, 0);
        }
        ofEndShape();
        ofPopMatrix();
        ofPopStyle();
    }
    
    
private:
    void update(ofEventArgs&){ buffer_.push_back(0); buffer_.pop_front();}
    ofRectangle area_;
    std::deque<int> buffer_;
    ofColor color_;
};
} // namespace orphe
} // namespace ofx




#endif // OFX_ORPHE_UTILITY_TRIGGERGRAPH_HPP_
