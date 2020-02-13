//
//  Signal.hpp
//
//  Created by Ryo Yumoto on 2020/02/12.
//

#ifndef OFX_ORPHE_SIGNAL_HPP_
#define OFX_ORPHE_SIGNAL_HPP_

#include <functional>
#include <vector>
#include "ofEvents.h"

namespace ofx{
namespace orphe{
template<typename T>
class Signal {
public:
    using callback_type = std::function<void(T&)>;
    Signal() { ofAddListener(event_, this, &Signal::call);}
    ~Signal(){ ofRemoveListener(event_, this, &Signal::call);}
    
    template<typename Callback>
    void connect(Callback&& callback){
        callback_collection_.push_back(std::forward<Callback>(callback));
    }
    
    void emit(T& arg){ ofNotifyEvent(event_, arg);}
private:
    ofEvent<T> event_;
    std::vector<callback_type> callback_collection_;
    void call(T& arg){
        for(auto& c : callback_collection_){
            if(c){ c(arg); }
        }
    }
};

template<>
class Signal<void> {
public:
    using callback_type = std::function<void(void)>;
    Signal() { ofAddListener(event_, this, &Signal::call);}
    ~Signal(){ ofRemoveListener(event_, this, &Signal::call);}
    
    template<typename Callback>
    void connect(Callback&& callback){
        callback_collection_.push_back(std::forward<Callback>(callback));
    }
    
    void emit(){ ofNotifyEvent(event_);}
    
private:
    ofEvent<void> event_;
    std::vector<callback_type> callback_collection_;
    void call(){
        for(auto& c : callback_collection_){
            if(c){ c(); }
        }
    }
};
} // namespace orphe
} // namespace ofx
#endif // OFX_ORPHE_SIGNAL_HPP_
