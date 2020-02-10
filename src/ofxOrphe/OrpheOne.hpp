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
    const glm::quat& getOrientationQuat() const { return orientation_quat_; }
    const glm::vec3& getOrientationEuler() const { return orientation_euler_; }
    const glm::vec3& getAcceleration() const { return acceleration_; }
    const glm::vec3& getGyro() const { return gyro_; }
    ofEvent<void>&   getHeelEvent() { return heel_;}
    ofEvent<void>&   getStepEvent() { return step_;}
    void             setOrientationQuat(const glm::quat& quat) { orientation_quat_ = quat; }
    void             setOrientationEuler(const glm::vec3& angle) { orientation_euler_ = angle; }
    void             setAccelaration(const glm::vec3& acc) { acceleration_ = acc; }
    void             setGyro(const glm::vec3& gyro) { gyro_ = gyro; }
    void             heel() { ofNotifyEvent(heel_); }
    void             step() { ofNotifyEvent(step_);}
private:
    glm::quat orientation_quat_;
    glm::vec3 orientation_euler_;
    glm::vec3 acceleration_;
    glm::vec3 gyro_;
    ofEvent<void> heel_;
    ofEvent<void> step_;
};
} // namespace orphe
} // namespace ofx

#endif // OFX_ORPHE_ORPHEONE_HPP_
