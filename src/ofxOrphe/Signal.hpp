//
//  Signal.hpp
//
//  Created by Ryo Yumoto on 2020/02/12.
//

#ifndef OFX_ORPHE_SIGNAL_HPP_
#define OFX_ORPHE_SIGNAL_HPP_

#include <functional>
#include "ofEvents.h"

template<typename T>
class Signal {
public:
    Signal() { ofAddListener(event_, this, &Signal::callback);}
    ~Signal(){ ofRemoveListener(event_, this, &Signal::callback);}
    
    template<typename Callback>
    void connect(Callback&& callback){
        callback_obj_ = std::forward<Callback>(callback);
    }
    
    void emit(T& arg){ ofNotifyEvent(event_, arg);}
private:
    ofEvent<T> event_;
    std::function<void(T&)> callback_obj_;
    void callback(T& arg){
        if(callback_obj_){
            callback_obj_(arg);
        }
    }
};

template<>
class Signal<void> {
public:
    Signal() { ofAddListener(event_, this, &Signal::callback);}
    ~Signal(){ ofRemoveListener(event_, this, &Signal::callback);}
    
    template<typename Callback>
    void connect(Callback&& callback){
        callback_obj_ = std::forward<Callback>(callback);
    }
    
    void emit(){ ofNotifyEvent(event_);}
    
private:
    ofEvent<void> event_;
    std::function<void(void)> callback_obj_;
    void callback(){
        if(callback_obj_){
            callback_obj_();
        }
    }
};

#endif // OFX_ORPHE_SIGNAL_HPP_
