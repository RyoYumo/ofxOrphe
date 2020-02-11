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
template<typename InputIterator, typename OutputIterator>
OutputIterator simpleMovingAverage(InputIterator first, InputIterator last, OutputIterator result){
    using c_value_type = typename std::iterator_traits<InputIterator>::value_type;
    auto sum = std::accumulate(first, last, c_value_type());
    result = sum / std::distance(first, last);
    return result;
}

template<typename InputIterator, typename OutputIterator>
OutputIterator weightedMovingAverage(InputIterator first, InputIterator last, OutputIterator result){
    using c_value_type = typename std::iterator_traits<InputIterator>::value_type;
    using c_diff_type  = typename std::iterator_traits<InputIterator>::difference_type;
    c_diff_type size   = std::distance(first, last);
    
    return result;
}


} // namespace orphe
} // namespace ofx

#endif // OFX_ORPHE_UTILITY_MOVINGAVERAGE_HPP_
