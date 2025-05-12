/// @file    Quat.cpp
/// @author  Matthew Green
/// @date    2025-05-10 18:13:47
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/math/Quat.hpp"
#include "velecs/math/Consts.hpp"
#include "velecs/math/Vec3.hpp"

#include <glm/gtc/quaternion.hpp>
// #include <glm/gtx/quaternion.hpp>

namespace velecs::math {

// Public Fields

const Quat Quat::IDENTITY = Quat(0.0f, 0.0f, 0.0f, 1.0f);

// Constructors and Destructors

Quat::Quat(const glm::quat& quat)
    : internal_quat(quat) {}

Quat::Quat(const float x, const float y, const float z, const float w)
    : internal_quat(w, x, y, z) {}

// Public Methods

Quat Quat::FromEulerAngles(const float x, const float y, const float z)
{
    // Convert to GLM's quaternion from Euler angles (in radians)
    // GLM uses the order Y-X-Z for Euler angle conversion
    return Quat(glm::quat(glm::vec3(x, y, z)));
}

Quat Quat::FromEulerAngles(const Vec3& angles)
{
    // Convert Vec3 to glm::vec3 and create quaternion
    return Quat(glm::quat(static_cast<glm::vec3>(angles)));
}

Quat Quat::FromEulerAnglesDeg(const float x, const float y, const float z)
{
    // Convert degrees to radians and create quaternion
    return FromEulerAngles(
        x * DEG_TO_RAD,
        y * DEG_TO_RAD,
        z * DEG_TO_RAD
    );
}

Quat Quat::FromEulerAnglesDeg(const Vec3& angles)
{
    // Convert degrees to radians and create quaternion
    return FromEulerAngles(angles * DEG_TO_RAD);
}

Vec3 Quat::ToEulerAngles() const
{
    // Extract Euler angles from quaternion (result in radians)
    glm::vec3 eulerAngles = glm::eulerAngles(internal_quat);
    
    // Convert to Vec3
    return Vec3(eulerAngles);
}

Vec3 Quat::ToEulerAnglesDeg() const
{
    // Get angles in radians, then convert to degrees
    Vec3 radAngles = ToEulerAngles();
    return Vec3(radAngles) * RAD_TO_DEG;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::math
