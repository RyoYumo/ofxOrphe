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
    SimpleMovingAverage() : data_(size),sum_(){}
    const T operator()(const T& input){
        sum_ += input;
        sum_ -= data_.front();
        data_.push_back(input); data_.pop_front();
        return sum_ / size;
    }
private:
    std::deque<T> data_;
    T sum_;
};


} // namespace orphe
} // namespace ofx

#endif // OFX_ORPHE_UTILITY_MOVINGAVERAGE_HPP_
