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
    velocity_sig_.emit(gait_.velocity);
}

void OrpheTrack::setOrientation(const glm::quat& quat) {
    gait_.orientation = quat;
    orientation_quat_sig_.emit(gait_.orientation);
}

void OrpheTrack::setDisplacement(const glm::vec3& displacement){
    gait_.displacement = displacement;
    displacement_sig_.emit(gait_.displacement);
}

void OrpheTrack::setDeltaDisplacement(const glm::vec3& delta_displacement){
    gait_.delta_displacement = delta_displacement;
    delta_displacement_sig_.emit(gait_.delta_displacement);
}

void OrpheTrack::setSpeed(float speed){
    gait_.speed = speed;
    speed_sig_.emit(gait_.speed);
}

void OrpheTrack::setPronation(float deg){
    gait_.pronation = deg;
    pronation_sig_.emit(gait_.pronation);
}

void OrpheTrack::setStrideDistance(float dist){
    gait_.stride_distance = dist;
    stride_distance_sig_.emit(gait_.stride_distance);
}

void OrpheTrack::setSwingDuration(float duration){
    gait_.swing_duration = duration;
    swing_duration_sig_.emit(gait_.swing_duration);
}

void OrpheTrack::setStanceDuration(float duration){
    gait_.stance_duration = duration;
    stance_duration_sig_.emit(gait_.stance_duration);
}


void OrpheTrack::setOrientation(const glm::vec3& euler){
    sensor_.orientation = euler;
    orientation_euler_sig_.emit(sensor_.orientation);
}

void OrpheTrack::setAcceleration(const glm::vec3& acc){
    sensor_.acceleration = acc;
    acceleration_sig_.emit(sensor_.acceleration);
}

void OrpheTrack::setGyro(const glm::vec3 &gyro){
    sensor_.gyro = gyro;
    gyro_sig_.emit(sensor_.gyro);
}

void OrpheTrack::setMagnitude(float mag){
    sensor_.magnitude = mag;
    magnitude_sig_.emit(sensor_.magnitude);
}

void OrpheTrack::setState(int state){
    using EnumType     = GaitAnalysisData::State;
    EnumType previous  = gait_.state;
    EnumType current   = static_cast<EnumType>(state);
    bool is_change = (previous != current) ? true : false;
    if(is_change){
        if(current == EnumType::kStop){
            stop_sig_.emit();
        }else if(current == EnumType::kWalk){
            walk_sig_.emit();
        }else if(current == EnumType::kRun){
            run_sig_.emit();
        }
    }
    gait_.state = current;
}

void OrpheTrack::setCyclePeriod(int period){
    using EnumType     = GaitAnalysisData::CyclePeriod;
    EnumType previous   = gait_.cycle_period;
    EnumType current  = static_cast<EnumType>(period);
    bool is_change = (previous != current) ? true : false;
    if(is_change){
        if(current == EnumType::kNone){
            cycle_period_none_sig_.emit();
        }else if(current == EnumType::kStance){
            cycle_period_stance_sig_.emit();
        }else if(current == EnumType::kSwing){
            cycle_period_swing_sig_.emit();
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
            detailed_cycle_period_none_sig_.emit();
        }else if (current == EnumType::kLoadingResponse){
            detailed_cycle_period_loading_response_sig_.emit();
        }else if (current == EnumType::kMidStance){
            detailed_cycle_period_mid_stance_sig_.emit();
        }else if (current == EnumType::kTerminalStance){
            detailed_cycle_period_termianl_stance_sig_.emit();
        }else if (current == EnumType::kIntialSwing){
            detailed_cycle_period_initial_swing_sig_.emit();
        }else if (current == EnumType::kMidSwing){
            detailed_cycle_period_mid_swing_sig_.emit();
        }else if (current == EnumType::kTerminalSwing){
            detailed_cycle_period_terminal_swing_sig_.emit();
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
            cycle_event_none_sig_.emit();
        }else if (current == EnumType::kInitial){
            cycle_event_initial_sig_.emit();
        }else if (current == EnumType::kFootFlat){
            cycle_event_foot_flat_sig_.emit();
        }else if (current == EnumType::kHeelRise){
            cycle_event_heel_rise_sig_.emit();
        }else if (current == EnumType::kToeOff){
            cycle_event_toe_off_sig_.emit();
        }else if (current == EnumType::kFeetAdjacent){
            cycle_event_feet_adjacent_sig_.emit();
        }else if (current == EnumType::kTibiaVertical){
            cycle_event_tibia_vertical_sig_.emit();
        }
    }
    
    gait_.cycle_event = current;
}

} // namespace orphe
} // namespace ofx
