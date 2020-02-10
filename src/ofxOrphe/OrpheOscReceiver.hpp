//
//  OrpheOscReceiver.hpp
//
//  Created by Ryo Yumoto on 2020/02/11.
//

#ifndef OFX_ORPHE_ORPHE_OSC_RECEIVER_HPP_
#define OFX_ORPHE_ORPHE_OSC_RECEIVER_HPP_

#include "OrpheOne.hpp"

namespace ofx {
namespace orphe {
//! osc interface
class OrpheOscReceiver {
public:
    OrpheOscReceiver();
    void left(OrpheOne* left);
    void right(OrpheOne* right);
    void subscribe(const int port=1234);
private:
    OrpheOne* left_;
    OrpheOne* right_;
};

} // namespace orphe
} // namespace ofx



#endif // OFX_ORPHE_ORPHE_OSC_RECEIVER_HPP_
