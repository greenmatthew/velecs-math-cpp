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
#include <glm/gtc/quaternion.hpp>

namespace velecs::math {

// Public Fields

const Quat Quat::IDENTITY = Quat(0.0f, 0.0f, 0.0f, 1.0f);

// Constructors and Destructors

// Public Methods

Quat Quat::FromEulerAnglesRad(const float x, const float y, const float z)
{
    // Convert to GLM's quaternion from Euler angles (in radians)
    // GLM uses the order Y-X-Z for Euler angle conversion
    return Quat(glm::quat(glm::vec3(x, y, z)));
}

Quat Quat::FromEulerAnglesRad(const Vec3& angles)
{
    // Convert Vec3 to glm::vec3 and create quaternion
    return Quat(glm::quat(static_cast<glm::vec3>(angles)));
}

Quat Quat::FromEulerAnglesDeg(const float x, const float y, const float z)
{
    // Convert degrees to radians and create quaternion
    return FromEulerAnglesRad(
        x * DEG_TO_RAD,
        y * DEG_TO_RAD,
        z * DEG_TO_RAD
    );
}

Quat Quat::FromEulerAnglesDeg(const Vec3& angles)
{
    // Convert degrees to radians and create quaternion
    return FromEulerAnglesRad(angles * DEG_TO_RAD);
}

Vec3 Quat::ToEulerAnglesRad() const
{
    return Vec3(glm::eulerAngles(internal_quat));
}

Vec3 Quat::ToEulerAnglesDeg() const
{
    return ToEulerAnglesRad() * RAD_TO_DEG;
}

Mat4 Quat::ToMatrix() const
{
    // Use GLM's built-in conversion from quaternion to mat4
    return Mat4(glm::mat4_cast(internal_quat));
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::math
