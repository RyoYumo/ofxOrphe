#pragma once

#include "ofMain.h"
#include "ofxOrphe.h"

template<std::size_t HistorySize>
class TriggerGraph {
public:
    static constexpr auto history_size = HistorySize;
    TriggerGraph(): history_(history_size),
                    area_(0, 0, 600, 300),
                    color_(ofColor::white)
    {
        ofAddListener(ofEvents().update, this, &TriggerGraph::update);
    }
    
    void setArea(const ofRectangle& area){
        area_ = area;
    }
    
    void setColor(const ofColor& color){
        color_ = color;
    }
    
    void trigger(){
        history_.back() = 1;
    }
    
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
        for(auto i = 0; i < history_.size(); ++i){
            if(i == 0) ofVertex(0, 0);
            auto x = i * ((float)area_.width / (history_.size()-1));
            auto y = history_[i] == 1 ? area_.height * -0.8 : 0.0;
            ofVertex(x,y);
            if(i == history_.size() -1) ofVertex(area_.width, 0);
        }
        ofEndShape();
        ofPopMatrix();
        ofPopStyle();
    }
    
    
private:
    void update(ofEventArgs&){
        history_.push_back(0); history_.pop_front();
    }
    ofRectangle area_;
    std::deque<int> history_;
    ofColor color_;
};



template<typename T, std::size_t HistorySize>
class ValueGraph {
public:
    using  value_type = T;
    static constexpr auto history_size = HistorySize;
    
    ValueGraph(): history_(history_size),
                  area_(0, 0, 600, 300),
                  color_(ofColor::white)
    {
    }
    
    void setArea(const ofRectangle& area){
        area_ = area;
    }
    
    void setColor(const ofColor& color){
           color_ = color;
    }
    
    void setInputValueRange(const T& from, const T& to){
        input_value_range_.first  = from;
        input_value_range_.second = to;
    }
    
    void value(const T& value){
        history_.push_back(value);
        history_.pop_front();
    }
    
    void draw(){
        ofPushStyle();
        ofNoFill();
        ofDrawRectangle(area_);
        ofPopStyle();

        ofPushStyle();
        ofSetColor(color_);
        ofPushMatrix();
        ofTranslate(area_.x, area_.y + area_.height * 0.5);
        ofBeginShape();
        for(auto i = 0; i < history_.size(); ++i){
            if(i == 0) ofVertex(0, 0);
            auto x = i * ((float)area_.width / (history_.size()-1));
            auto y = -1 * ofMap(ofClamp(history_[i],
                                input_value_range_.first,
                                input_value_range_.second),
                                input_value_range_.first,
                                input_value_range_.second,
                                -1.0,
                                1.0);
            
            ofVertex(x,y * area_.height * 0.5);
            if(i == history_.size() -1) ofVertex(area_.width, 0);
        }
        ofEndShape();
        ofPopMatrix();
        ofPopStyle();
    }
    
    T getValue() const { return history_.back(); }
    
private:
    ofRectangle area_;
    std::deque<T> history_;
    ofColor color_;
    std::pair<T, T> input_value_range_;
};



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
    static constexpr auto HistorySize = 100;
    TriggerGraph<HistorySize> left_swing_history;
    TriggerGraph<HistorySize> left_stance_history;
    TriggerGraph<HistorySize> right_swing_history;
    TriggerGraph<HistorySize> right_stance_history;
    ValueGraph<float,50>   swing_duration_diff_hisotry;
    ValueGraph<float,50>   stance_duration_diff_hisotry;
};
