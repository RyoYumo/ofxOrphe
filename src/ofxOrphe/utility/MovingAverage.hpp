//
//  MovingAverage.hpp
//
//  Created by Ryo Yumoto on 2020/02/11.
//

#ifndef OFX_ORPHE_UTILITY_MOVINGAVERAGE_HPP_
#define OFX_ORPHE_UTILITY_MOVINGAVERAGE_HPP_

#include <algorithm>
#include <deque>
#include <iterator>
#include <numeric>

namespace ofx {
namespace orphe {

template<typename T, std::size_t N>
class SimpleMovingAverage {
public:
    using value_type = T;
    static constexpr auto size = N;
    SimpleMovingAverage() : data_(size),sum_(), denominator_(){
        denominator_ = size;
    }
    const T getOutput(const T& input){
        data_.push_back(input);
        data_.pop_front();
        sum_ = T{};
        
        for(auto i = 0; i < size; ++i){
            sum_ += data_.at(i);
        }
        
        return sum_ / denominator_;
    }
private:
    std::deque<T> data_;
    T sum_;
    int denominator_;
};

template<typename T, std::size_t N>
class WeightedMovingAverage {
public:
    using value_type = T;
    static constexpr auto size = N;
    WeightedMovingAverage() : data_(size), weight_(), sum_(), denominator_(){
        for(auto i = 0; i < size; ++i){
            weight_.push_back(size - i);
            denominator_ += (size - i);
        }
    }
    const T getOutput(const T& input){
        data_.push_back(input);
        data_.pop_front();
        sum_ = T{};
        
        for(auto i = 0; i < size; ++i){
            sum_ += weight_.at(i) * data_.at(i);
        }
        
        return sum_ / denominator_;
    }
private:
    std::deque<T> data_;
    std::vector<std::size_t> weight_;
    T sum_;
    int denominator_;
};

template<typename T, std::size_t N>
class ExponentialMovingAverage {
public:
    using value_type = T;
    static constexpr auto size = N;
    ExponentialMovingAverage() : data_(size), weight_(), sum_(), alpha_(), denominator_(){
        alpha_ = 2/ (size + 1);
        weight_.push_back(1);
        for(auto i = 1; i <= size; ++i){
            weight_.push_back(std::pow(1-alpha_, i));
            denominator_ += std::pow(1-alpha_, i);
        }
        denominator_ = denominator_ + 1;
    }
    const T getOutput(const T& input){
        data_.push_back(input);
        data_.pop_front();
        sum_ = T{};
        
        for(auto i = 0; i <= size; ++i){
            sum_ += weight_.at(i) * data_.at(i);
        }
        
        return sum_ / denominator_;
    }
private:
    std::deque<T> data_;
    std::vector<std::size_t> weight_;
    T sum_;
    float alpha_;
    float denominator_;
};

template<typename T, std::size_t N>
class ModifiedMovingAverage {
public:
    using value_type = T;
    static constexpr auto size = N;
    ModifiedMovingAverage() : data_(size), weight_(), sum_(), alpha_(), denominator_(){
        alpha_ = 1/size;
        weight_.push_back(1);
        for(auto i = 1; i <= size; ++i){
            weight_.push_back(std::pow(1-alpha_, i));
            denominator_ += std::pow(1-alpha_, i);
        }
        denominator_ = denominator_ + 1;
    }
    const T getOutput(const T& input){
        data_.push_back(input);
        data_.pop_front();
        sum_ = T{};
        
        for(auto i = 0; i <= size; ++i){
            sum_ += weight_.at(i) * data_.at(i);
        }
        
        return sum_ / denominator_;
    }
private:
    std::deque<T> data_;
    std::vector<std::size_t> weight_;
    T sum_;
    float alpha_;
    float denominator_;
};

template<typename T, std::size_t N>
class TriangularMovingAverage {
public:
    using value_type = T;
    static constexpr auto size = N;
    TriangularMovingAverage() : w_(), sma_(), out_(){
        w_ = glm::ceil((size+1)/2);
    }
    const T getOutput(const T& input){
        return out_.getOutput(sma_.getOutput(input));
    }
private:
    std::size_t w_;
    SimpleMovingAverage<float, w_> sma_;
    SimpleMovingAverage<float, w_> out_;
};


} // namespace orphe
} // namespace ofx

#endif // OFX_ORPHE_UTILITY_MOVINGAVERAGE_HPP_
