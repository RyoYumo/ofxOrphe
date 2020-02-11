//
//  OrpheOne.hpp
//
//  Created by Ryo Yumoto on 2020/02/11.
//

#ifndef OFX_ORPHE_ORPHEONE_HPP_
#define OFX_ORPHE_ORPHEONE_HPP_

#include "glm/gtc/quaternion.hpp"
#include "glm/glm.hpp"
#include "ofEvents.h"

namespace ofx{
namespace orphe{
class OrpheOne {
public:
    const glm::quat& getOrientationQuat() const { return sensor_data_.orientation_quat; }
    const glm::vec3& getOrientationEuler() const { return sensor_data_.orientation_euler; }
    const glm::vec3& getAcceleration() const { return sensor_data_.accleration; }
    const glm::vec3& getGyro() const { return sensor_data_.gyro; }
    ofEvent<void>&   getHeelEvent() { return gesture_.heel;}
    ofEvent<void>&   getStepEvent() { return gesture_.step;}
    void             setOrientationQuat(const glm::quat& quat) { sensor_data_.orientation_quat = quat; }
    void             setOrientationEuler(const glm::vec3& angle) { sensor_data_.orientation_euler = angle; }
    void             setAccelaration(const glm::vec3& acc) { sensor_data_.accleration = acc; }
    void             setGyro(const glm::vec3& gyro) { sensor_data_.gyro = gyro; }
    void             heel() { ofNotifyEvent(gesture_.heel);}
    void             step() { ofNotifyEvent(gesture_.step);}
private:
    struct SensorData {
        glm::quat orientation_quat;
        glm::vec3 orientation_euler;
        glm::vec3 accleration;
        glm::vec3 gyro;
    };
    
    struct Gesture {
        ofEvent<void> heel;
        ofEvent<void> step;
    };
    SensorData  sensor_data_;
    Gesture     gesture_;
};
} // namespace orphe
} // namespace ofx

#endif // OFX_ORPHE_ORPHEONE_HPP_
