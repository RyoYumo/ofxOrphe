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
template<typename T>
class SimpleMovingAverage {
public:
    SimpleMovingAverage(const int size) : data_(size), size_(size), sum_(){}
    const T operator()(const T& input){
        data_.push_back(input); data_.pop_front();
        sum_ += data_.back();
        sum_ -= data_.front();
        return sum_ / size_;
    }
    const std::size_t size() const { return size_; }
private:
    std::deque<T> data_;
    std::size_t   size_;
    T sum_;
};


} // namespace orphe
} // namespace ofx

#endif // OFX_ORPHE_UTILITY_MOVINGAVERAGE_HPP_
