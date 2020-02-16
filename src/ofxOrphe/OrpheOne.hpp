//
//  OrpheOne.hpp
//
//  Created by Ryo Yumoto on 2020/02/11.
//

#ifndef OFX_ORPHE_ORPHEONE_HPP_
#define OFX_ORPHE_ORPHEONE_HPP_

#include "glm/gtc/quaternion.hpp"
#include "glm/glm.hpp"
#include "Signal.hpp"
#include "ofEvents.h"

namespace ofx{
namespace orphe{
class OrpheOne {
public:
    void                setOrientation(const glm::vec3& euler) { sensor_.orientation = euler; orientation_sig_.emit(sensor_.orientation); }
    void                setAcceleration(const glm::vec3& acc) { sensor_.acceleration = acc; acceleration_sig_.emit(sensor_.acceleration);}
    void                setGyro(const glm::vec3& gyro) { sensor_.gyro = gyro; gyro_sig_.emit(sensor_.gyro); }
    void                setManitude(float mag) { sensor_.magnitude = mag; magnitude_sig_.emit(sensor_.magnitude);}
    const glm::vec3&    getOrientation() const { return sensor_.orientation; }
    const glm::vec3&    getAcceleration() const { return sensor_.acceleration; }
    const glm::vec3&    getGyro() const { return sensor_.gyro; }
    const float         getMagnitude() const { return sensor_.magnitude; }
    Signal<glm::vec3>&  getOrientationSignal() { return orientation_sig_; }
    Signal<glm::vec3>&  getAccelerationSignal() { return acceleration_sig_; }
    Signal<glm::vec3>&  getGyroSignal() { return gyro_sig_;}
    Signal<float>&      getMagnitudeSignal() { return magnitude_sig_; }
private:
    struct SensorData {
           glm::vec3     orientation;
           glm::vec3     acceleration;
           glm::vec3     gyro;
           float         magnitude;
    };
    SensorData sensor_;
    Signal<glm::vec3> orientation_sig_;
    Signal<glm::vec3> acceleration_sig_;
    Signal<glm::vec3> gyro_sig_;
    Signal<float>     magnitude_sig_;
};
} // namespace orphe
} // namespace ofx

#endif // OFX_ORPHE_ORPHEONE_HPP_
