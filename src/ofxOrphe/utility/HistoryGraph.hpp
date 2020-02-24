//
//  HistoryGraph.hpp
//  example-sensor
//
//  Created by Ryo Yumoto on 2020/02/24.
//

#ifndef OFX_ORPHE_UTILITY_HISTORYGRAPH_HPP_
#define OFX_ORPHE_UTILITY_HISTORYGRAPH_HPP_
#include "ofMain.h"

namespace ofx{
namespace orphe {
template<typename T, std::size_t BufferSize>
class HistoryGraph {
public:
    enum class InputRangeType { kPositive, kNegative, kPositiveAndNegative };
    using  value_type          =  T;
    static constexpr auto size = BufferSize;
    HistoryGraph() : is_fill_{true}, color_{ofColor::white}, input_min_(0.0), input_max_{1.0}, buffer_(size){}
    
    void fill() { is_fill_ = true;}
    void noFill() { is_fill_ = false; }
    void setColor(const ofColor& color) { color_ = color; }
    void setInputValueRange(T min, T max) {
        if(min > max) return;
        input_min_ = min; input_max_ = max;
        input_range_type_ = checkInputRangeType(input_min_, input_max_);
    }
    
    void addValue(const T& value){
        buffer_.push_back(value);
        buffer_.pop_front();
    }
    
    T   getValue() const { return buffer_.back(); }
    
    void setDrawingArea(const ofRectangle& area) { area_ = area; }
    void draw() const {
        ofPushStyle();
        ofPushMatrix();
        ofNoFill();
        ofDrawRectangle(area_);
        
        float y_min, y_max;
        
        // translate
        if(input_range_type_ == InputRangeType::kPositive){
            ofTranslate(area_.x, area_.y + area_.height);
            y_min = 0.0; y_max = 1.0;
        }else if (input_range_type_ == InputRangeType::kNegative){
            ofTranslate(area_.x, area_.y);
            y_min = -1.0; y_max = 0.0;
        }else{
            ofTranslate(area_.x, area_.y + area_.height * 0.5);
            y_min = -1.0; y_max = 1.0;
        }
        
        ofSetColor(color_);
        is_fill_ ? ofFill() : ofNoFill();
        
        ofBeginShape();
        for(auto i = 0; i < buffer_.size(); ++i){
            float x =  i * ((float)area_.width / (buffer_.size() - 1));
            float y = -1 * ofMap(ofClamp(buffer_[i], input_min_, input_max_), input_min_,input_max_, y_min, y_max);
            if(is_fill_ && i == 0) ofVertex(0, 0);
            auto scale = input_range_type_ == InputRangeType::kPositiveAndNegative ? area_.height * 0.5 : area_.height;
            ofVertex(x, scale * y);
            if(is_fill_ && i == buffer_.size()-1) ofVertex(area_.width,0);
        }
        ofEndShape();
        ofPopMatrix();
        ofPopStyle();
    }
    
private:
    InputRangeType checkInputRangeType(T min, T max){
        if(min >= 0 && max >= 0) return InputRangeType::kPositive;
        else if (min<0 && max >= 0) return InputRangeType::kPositiveAndNegative;
        else return InputRangeType::kNegative;
    }
    
    bool          is_fill_;
    ofColor       color_;
    T             input_min_;
    T             input_max_;
    InputRangeType input_range_type_;
    std::deque<T> buffer_;
    ofRectangle   area_;
};



} // namespace orphe
} // namespace ofx





#endif // OFX_ORPHE_UTILITY_HISTORYGRAPH_HPP_
