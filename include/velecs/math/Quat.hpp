/// @file    Quat.hpp
/// @author  Matthew Green
/// @date    2025-05-10 18:13:28
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/math/Mat4.hpp"

#include <glm/ext/quaternion_float.hpp>

namespace velecs::math {

struct Vec3;

/// @struct Quat
/// @brief A quaternion class for representing 3D rotations.
///
/// Quaternions efficiently represent 3D rotations while avoiding gimbal lock.
/// This class wraps GLM's quaternion with a consistent interface using the
/// game engine convention of (x,y,z,w) component ordering.
struct Quat {
public:
    // Enums

    // Public Fields

    static const Quat IDENTITY; /// @brief Identity quaternion that represents no rotation (0, 0, 0, 1).

    glm::quat internal_quat; /// @brief The internal GLM quaternion.

    // Constructors and Destructors

    /// @brief Construct from glm::quat
    /// @param quat The GLM quaternion to copy
    inline Quat(const glm::quat& quat)
        : internal_quat(quat) {}

    /// @brief Construct a quaternion from components
    /// @param x X component of the quaternion (imaginary i component)
    /// @param y Y component of the quaternion (imaginary j component)
    /// @param z Z component of the quaternion (imaginary k component)
    /// @param w W component of the quaternion (real component)
    /// @note Parameter order follows the common game engine convention (x,y,z,w).
    ///       This differs from mathematical notation and GLM's internal order (w,x,y,z),
    ///       but provides consistency with engines like Unity and Unreal.
    Quat(const float x, const float y, const float z, const float w)
        : internal_quat(w, x, y, z) {}

    /// @brief Default deconstructor.
    ~Quat() = default;

    // Public Methods

    /// @brief Create a quaternion from Euler angles
    /// @param x Rotation around X-axis in radians
    /// @param y Rotation around Y-axis in radians
    /// @param z Rotation around Z-axis in radians
    /// @return A quaternion representing the specified rotation
    static Quat FromEulerAnglesRad(const float x, const float y, const float z);
    
    /// @brief Create a quaternion from Euler angles
    /// @param angles Vector of rotation angles in radians (x, y, z)
    /// @return A quaternion representing the specified rotation
    static Quat FromEulerAnglesRad(const Vec3& angles);
    
    /// @brief Create a quaternion from Euler angles in degrees
    /// @param x Rotation around X-axis in degrees
    /// @param y Rotation around Y-axis in degrees
    /// @param z Rotation around Z-axis in degrees
    /// @return A quaternion representing the specified rotation
    static Quat FromEulerAnglesDeg(const float x, const float y, const float z);
    
    /// @brief Create a quaternion from Euler angles in degrees
    /// @param angles Vector of rotation angles in degrees (x, y, z)
    /// @return A quaternion representing the specified rotation
    static Quat FromEulerAnglesDeg(const Vec3& angles);

    /// @brief Convert this quaternion to Euler angles
    /// @return A Vec3 containing the Euler angles in radians (x, y, z)
    Vec3 ToEulerAnglesRad() const;
    
    /// @brief Convert this quaternion to Euler angles in degrees
    /// @return A Vec3 containing the Euler angles in degrees (x, y, z)
    Vec3 ToEulerAnglesDeg() const;

    /// @brief Converts the quaternion to a rotation matrix
    /// @return A Mat4 representing the rotation described by this quaternion
    Mat4 ToMatrix() const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::math
