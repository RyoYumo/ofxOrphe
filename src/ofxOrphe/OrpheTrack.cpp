//
//  OrpheTrack.cpp
//
//  Created by Ryo Yumoto on 2020/02/11.
//

#include "OrpheTrack.hpp"

namespace ofx{
namespace orphe{
void OrpheTrack::setVelocity(const glm::vec3 &velocity){
    gait_.velocity = velocity;
    velocity_sig_.notify(gait_.velocity);
}

void OrpheTrack::setOrientation(const glm::quat& quat) {
    gait_.orientation = quat;
    orientation_sig_.notify(gait_.orientation);
}

void OrpheTrack::setDisplacement(const glm::vec3& displacement){
    gait_.displacement = displacement;
    displacement_sig_.notify(gait_.displacement);
}

void OrpheTrack::setDeltaDisplacement(const glm::vec3& delta_displacement){
    gait_.delta_displacement = delta_displacement;
    delta_displacement_sig_.notify(gait_.delta_displacement);
}

void OrpheTrack::setSpeed(float speed){
    gait_.speed = speed;
    speed_sig_.notify(gait_.speed);
}

void OrpheTrack::setSwingDuration(float duration){
    gait_.swing_duration = duration;
    swing_duration_sig_.notify(gait_.swing_duration);
}

void OrpheTrack::setStanceDuration(float duration){
    gait_.stance_duration = duration;
    stance_duration_sig_.notify(gait_.stance_duration);
}

void OrpheTrack::setState(int state){
    using EnumType     = GaitAnalysisData::State;
    EnumType previous  = gait_.state;
    EnumType current   = static_cast<EnumType>(state);
    bool is_change = (previous != current) ? true : false;
    if(is_change){
        if(current == EnumType::kStop){
            stop_sig_.notify();
        }else if(current == EnumType::kWalk){
            walk_sig_.notify();
        }else if(current == EnumType::kRun){
            run_sig_.notify();
        }
    }
}

void OrpheTrack::setCyclePeriod(int period){
    using EnumType     = GaitAnalysisData::CyclePeriod;
    EnumType previous   = gait_.cycle_period;
    EnumType current  = static_cast<EnumType>(period);
    bool is_change = (previous != current) ? true : false;
    if(is_change){
        if(current == EnumType::kNone){
            cycle_period_none_sig_.notify();
        }else if(current == EnumType::kStance){
            cycle_period_stance_sig_.notify();
        }else if(current == EnumType::kSwing){
            cycle_period_swing_sig_.notify();
        }
    }
    
    gait_.cycle_period = current;
}


void OrpheTrack::setDetailedCyclePeriod(int period){
    using EnumType     = GaitAnalysisData::DetailedCyclePeriod;
    EnumType previous  = gait_.detailed_cycle_period;
    EnumType current   = static_cast<EnumType>(period);
    
    bool is_change = (previous != current) ? true : false;
    if(is_change){
        if(current == EnumType::kNone){
            detailed_cycle_period_none_sig_.notify();
        }else if (current == EnumType::kLoadingResponse){
            detailed_cycle_period_loading_response_sig_.notify();
        }else if (current == EnumType::kMidStance){
            detailed_cycle_period_mid_stance_sig_.notify();
        }else if (current == EnumType::kTerminalStance){
            detailed_cycle_period_termianl_stance_sig_.notify();
        }else if (current == EnumType::kIntialSwing){
            detailed_cycle_period_initial_swing_sig_.notify();
        }else if (current == EnumType::kMidSwing){
            detailed_cycle_period_mid_swing_sig_.notify();
        }else if (current == EnumType::kTerminalSwing){
            detailed_cycle_period_terminal_swing_sig_.notify();
        }
    }
    
    gait_.detailed_cycle_period = current;
}

void OrpheTrack::setCycleEvent(int event){
    using EnumType     = GaitAnalysisData::CycleEvent;
    EnumType previous  = gait_.cycle_event;
    EnumType current   = static_cast<EnumType>(event);
    
    bool is_change = (previous != current) ? true : false;
    if(is_change){
        if(current == EnumType::kNone){
            cycle_event_none_sig_.notify();
        }else if (current == EnumType::kInitial){
            cycle_event_initial_sig_.notify();
        }else if (current == EnumType::kFootFlat){
            cycle_event_foot_flat_sig_.notify();
        }else if (current == EnumType::kHeelRise){
            cycle_event_heel_rise_sig_.notify();
        }else if (current == EnumType::kToeOff){
            cycle_event_toe_off_sig_.notify();
        }else if (current == EnumType::kFeetAdjacent){
            cycle_event_feet_adjacent_sig_.notify();
        }else if (current == EnumType::kTibiaVertical){
            cycle_event_tibia_vertical_sig_.notify();
        }
    }
    
    gait_.cycle_event = current;
}

} // namespace orphe
} // namespace ofx
