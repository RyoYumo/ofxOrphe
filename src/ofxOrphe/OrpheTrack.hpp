//
//  OrpheTrack.hpp
//
//  Created by Ryo Yumoto on 2020/02/11.
//

#ifndef OFX_ORPHE_ORPHETRACK_HPP_
#define OFX_ORPHE_ORPHETRACK_HPP_

#include "glm/gtc/quaternion.hpp"
#include "glm/glm.hpp"
#include "ofEvents.h"
#include "Signal.hpp"
#include <unordered_map>

namespace ofx{
namespace orphe {
namespace detail{
template<typename E>
typename std::underlying_type<E>::type
toUType(E enumerator){
    using ReturnType = typename std::underlying_type<E>::type;
    return static_cast<ReturnType>(enumerator);
}
} // namespace detail

class OrpheTrack {
    friend class OrpheTrackOscReceiver;
public:
    //! getter
    const glm::quat&   getOrientationQuat() const { return gait_.orientation; }
    const glm::vec3&   getVelocity() const { return gait_.velocity; }
    const glm::vec3&   getDisplacement() const { return gait_.displacement;}
    const glm::vec3&   getDeltaDisplacement() const { return gait_.delta_displacement; }
    const float        getSwingDuration() const { return gait_.swing_duration; }
    const float        getStanceDuration() const { return gait_.stance_duration; }
    const float        getSpeed() const { return gait_.speed;}
    const float        getPronation() const { return gait_.pronation;}
    const float        getStrideDistance() const { return gait_.stride_distance;}
    const float        getStrikeAngle() const { return gait_.strike_angle; }
    const int          getState() const { return detail::toUType(gait_.state);}
    const int          getCyclePeriod() const { return detail::toUType(gait_.cycle_period);}
    const int          getDetailedCyclePeriod() const { return detail::toUType(gait_.detailed_cycle_period); }
    const int          getCycleEvent() const { return detail::toUType(gait_.cycle_event); }
    
    //! signal getter (event)
    Signal<glm::vec3>& getVelocitySignal() { return velocity_sig_; }
    Signal<glm::quat>& getOrientationQuatSignal() { return orientation_quat_sig_; }
    Signal<glm::vec3>& getDisplacementSignal() { return displacement_sig_; }
    Signal<float>&     getSpeedSignal() { return speed_sig_; }
    Signal<float>&     getPronationSignal() { return pronation_sig_; }
    Signal<float>&     getStrideDistanceSignal() { return stride_distance_sig_; }
    Signal<float>&     getStanceDurationSignal() { return stance_duration_sig_; }
    Signal<float>&     getSwingDurationSignal() { return swing_duration_sig_;}
    Signal<float>&     getStrikeAngleSignal() { return strike_angle_sig_;}
    Signal<void>&      getStopSignal() { return stop_sig_; }
    Signal<void>&      getWalkSignal() { return walk_sig_; }
    Signal<void>&      getRunSignal() { return  run_sig_; }
    Signal<void>&      getCyclePeriodNoneSignal() { return cycle_period_none_sig_; }
    Signal<void>&      getCyclePeriodStanceSignal() { return cycle_period_stance_sig_; }
    Signal<void>&      getCyclePeriodSwingSignal() { return cycle_period_swing_sig_; }
    Signal<void>&      getDetailedCyclePeriodNoneSignal() { return detailed_cycle_period_none_sig_; }
    Signal<void>&      getDetailedCyclePeriodLoadingResponseSignal() { return detailed_cycle_period_loading_response_sig_; }
    Signal<void>&      getDetailedCyclePeriodMidStanceSignal() { return detailed_cycle_period_mid_stance_sig_; }
    Signal<void>&      getDetailedCyclePeriodTerminalStanceSignal() { return detailed_cycle_period_termianl_stance_sig_; }
    Signal<void>&      getDetailedCyclePeriodInitialSwingSignal() { return detailed_cycle_period_initial_swing_sig_; }
    Signal<void>&      getDetailedCyclePeriodMidSwingSignal() { return detailed_cycle_period_mid_swing_sig_; }
    Signal<void>&      getDetailedCyclePeriodTerminalSwingSignal() { return detailed_cycle_period_terminal_swing_sig_; }
    Signal<void>&      getCycleEventNoneSignal() { return cycle_event_none_sig_;}
    Signal<void>&      getCycleEventInitialSignal() { return cycle_event_initial_sig_;}
    Signal<void>&      getCycleEventFootFlatSignal() { return cycle_event_foot_flat_sig_;}
    Signal<void>&      getCycleEventHeelRiseSignal() { return cycle_event_heel_rise_sig_;}
    Signal<void>&      getCycleEventToeOffSignal() { return cycle_event_toe_off_sig_;}
    Signal<void>&      getCycleEventFeetAdjacentSignal() { return cycle_event_feet_adjacent_sig_;}
    Signal<void>&      getCycleEventTibiaVerticalSignal() { return cycle_event_tibia_vertical_sig_;}
    
    
    //! getter
    const glm::vec3& getOrientationEuler() const { return sensor_.orientation; }
    const glm::vec3& getAcceleration() const { return sensor_.acceleration; }
    const glm::vec3& getGyro() const { return sensor_.gyro; }
    const float      getMagnitude() const { return sensor_.magnitude; }
    
    Signal<glm::vec3>& getOrientationEulerSignal() { return orientation_euler_sig_; }
    Signal<glm::vec3>& getAccelerationSignal() { return acceleration_sig_;}
    Signal<glm::vec3>& getGyroSignal() { return gyro_sig_; }
    Signal<float>&     getMagnitudeSignal() { return magnitude_sig_; }
    
private:
    struct GaitAnalysisData {
        enum class State { kStop, kWalk, kRun };
        enum class CyclePeriod { kNone, kStance, kSwing };
        enum class DetailedCyclePeriod { kNone, kLoadingResponse, kMidStance, kTerminalStance, kIntialSwing, kMidSwing, kTerminalSwing };
        enum class CycleEvent { kNone, kInitial, kFootFlat, kHeelRise, kToeOff, kFeetAdjacent, kTibiaVertical };
        glm::quat orientation;
        glm::vec3 velocity;
        glm::vec3 displacement;
        glm::vec3 delta_displacement;
        float strike_angle;
        float swing_duration;
        float stance_duration;
        float speed;     // km/h
        float pronation; // deg
        float stride_distance; // m
        State state;
        CyclePeriod cycle_period;
        DetailedCyclePeriod detailed_cycle_period;
        CycleEvent cycle_event;
    };
    
    struct SensorData {
        glm::vec3     orientation;
        glm::vec3     acceleration;
        glm::vec3     gyro;
        float         magnitude;
    };
    
    GaitAnalysisData  gait_;
    SensorData        sensor_;
    Signal<glm::quat> orientation_quat_sig_;
    Signal<glm::vec3> velocity_sig_;
    Signal<glm::vec3> displacement_sig_;
    Signal<glm::vec3> delta_displacement_sig_;
    Signal<float>     stance_duration_sig_;
    Signal<float>     strike_angle_sig_;
    Signal<float>     swing_duration_sig_;
    Signal<float>     speed_sig_;
    Signal<float>     pronation_sig_;
    Signal<float>     stride_distance_sig_;
    
    // state
    Signal<void>      stop_sig_;
    Signal<void>      walk_sig_;
    Signal<void>      run_sig_;
    
    // cycle period
    Signal<void>      cycle_period_none_sig_;
    Signal<void>      cycle_period_stance_sig_;
    Signal<void>      cycle_period_swing_sig_;
    
    // detailed cycle period
    Signal<void>      detailed_cycle_period_none_sig_;
    Signal<void>      detailed_cycle_period_loading_response_sig_;
    Signal<void>      detailed_cycle_period_mid_stance_sig_;
    Signal<void>      detailed_cycle_period_termianl_stance_sig_;
    Signal<void>      detailed_cycle_period_initial_swing_sig_;
    Signal<void>      detailed_cycle_period_mid_swing_sig_;
    Signal<void>      detailed_cycle_period_terminal_swing_sig_;
    
    // cycle event
    Signal<void>      cycle_event_none_sig_;
    Signal<void>      cycle_event_initial_sig_;
    Signal<void>      cycle_event_foot_flat_sig_;
    Signal<void>      cycle_event_heel_rise_sig_;
    Signal<void>      cycle_event_toe_off_sig_;
    Signal<void>      cycle_event_feet_adjacent_sig_;
    Signal<void>      cycle_event_tibia_vertical_sig_;
    
    // sensor
    Signal<glm::vec3> orientation_euler_sig_;
    Signal<glm::vec3> acceleration_sig_;
    Signal<glm::vec3> gyro_sig_;
    Signal<float>     magnitude_sig_;
    
 
    void setVelocity(const glm::vec3& velocity);
    void setOrientation(const glm::quat& quat);
    void setDisplacement(const glm::vec3& displacement);
    void setDeltaDisplacement(const glm::vec3& delta_displacement);
    void setSwingDuration(float duration);
    void setStanceDuration(float duration);
    void setSpeed(float speed);
    void setPronation(float deg);
    void setStrideDistance(float dist);
    void setState(int state);
    void setCyclePeriod(int period);
    void setDetailedCyclePeriod(int period);
    void setCycleEvent(int event);
    void setStrikeAngle(float deg);
    void setOrientation(const glm::vec3& euler);
    void setAcceleration(const glm::vec3& acc);
    void setGyro(const glm::vec3& gyro);
    void setMagnitude(float mag);

};

} // namespace orphe
} // namespace ofx



#endif // OFX_ORPHE_ORPHETRACK_HPP_
