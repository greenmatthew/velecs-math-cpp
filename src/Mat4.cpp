/// @file    Mat4.cpp
/// @author  Matthew Green
/// @date    2025-05-09 17:33:54
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/math/Mat4.hpp"
#include "velecs/math/Vec3.hpp"
#include "velecs/math/Vec4.hpp"
#include "velecs/math/Quat.hpp"

namespace velecs::math {

// Public Fields

const Mat4 Mat4::IDENTITY = glm::mat4(1.0f);
const Mat4 Mat4::ZERO = glm::mat4(0.0f);
const Mat4 Mat4::NEG_IDENTITY = glm::mat4(-1.0f);

// Constructors and Destructors

Mat4::Mat4(float diagonal)
    : internal_mat(glm::mat4(diagonal)) {}

// Public Methods

Mat4 Mat4::FromPosition(const Vec3& position)
{
    glm::mat4 internal = glm::mat4(1.0f);
    internal[3][0] = position.x;
    internal[3][1] = position.y;
    internal[3][2] = position.z;
    return Mat4(internal);
}

Mat4 Mat4::FromScale(const Vec3& scale)
{
    glm::mat4 internal = glm::mat4(1.0f);
    internal[0][0] = scale.x;
    internal[1][1] = scale.y;
    internal[2][2] = scale.z;
    return Mat4(internal);
}

Mat4 Mat4::FromRotation(const Vec3& rotation)
{
    return Quat::FromEulerAngles(rotation).ToMatrix();
}

Mat4 Mat4::FromRotationDeg(const Vec3& rotationDeg)
{
    return Quat::FromEulerAnglesDeg(rotationDeg).ToMatrix();
}

Mat4 Mat4::FromPerspective(float verticalFov, float aspectRatio, float nearPlane, float farPlane)
{
    // Define the coordinate system change matrix (X)
    glm::mat4 X = glm::mat4(1.0f); // Start with an identity matrix
    X[1][1] = -1.0f; // Flip Y axis
    X[2][2] = -1.0f; // Flip Z axis

    const float vFovRads = DEG_TO_RAD * verticalFov;
    const float focalLength = 1.0f / (std::tanf(vFovRads * 0.5f));
    const float x = focalLength / aspectRatio;
    const float y = focalLength;
    const float A = farPlane / (farPlane - nearPlane);
    const float B = -nearPlane * A;

    // Define the right-handed perspective projection matrix manually
    glm::mat4 perspectiveMatrix = glm::mat4(0.0f); // Initialize all elements to 0
    perspectiveMatrix[0][0] = x;
    perspectiveMatrix[1][1] = y; // Negative for Vulkan's Y-axis
    perspectiveMatrix[2][2] = A;
    perspectiveMatrix[2][3] = 1.0f; // For perspective projection
    perspectiveMatrix[3][2] = B;

    // Combine the projection matrix with the coordinate system change matrix
    // This is because Vulkan switches coordinate systems between world space and NDC space.
    // Pre-applying this change to the perspective matrix so it is not forgotten.
    return Mat4(perspectiveMatrix * X);
}

Mat4 Mat4::FromOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    // Define the coordinate system change matrix (X)
    glm::mat4 X = glm::mat4(1.0f);
    X[1][1] = -1.0f; // Flip Y axis
    X[2][2] = -1.0f; // Flip Z axis

    // Calculate the scale factors
    float scaleX = 2.0f / (right - left);
    float scaleY = 2.0f / (top - bottom);
    float scaleZ = 1.0f / (farPlane - nearPlane); // Scale to [0,1] for Vulkan

    // Calculate the translation factors
    float transX = -(right + left) / (right - left);
    float transY = -(top + bottom) / (top - bottom);
    float transZ = -nearPlane / (farPlane - nearPlane); // Offset for Vulkan's [0,1] Z range

    // Create the orthographic projection matrix
    glm::mat4 orthoMatrix = glm::mat4(0.0f);
    orthoMatrix[0][0] = scaleX;
    orthoMatrix[1][1] = scaleY;
    orthoMatrix[2][2] = scaleZ;
    orthoMatrix[3][0] = transX;
    orthoMatrix[3][1] = transY;
    orthoMatrix[3][2] = transZ;
    orthoMatrix[3][3] = 1.0f;

    // Apply the coordinate system change
    return Mat4(orthoMatrix * X);
}

Mat4& Mat4::operator*=(const Mat4& other)
{
    internal_mat = internal_mat * other.internal_mat;
    return *this; // Return ref to allow chaining assignment operations
}

Mat4& Mat4::Translate(const Vec3& displacement)
{
    *this = WithTranslation(displacement);
    return *this;
}

Mat4& Mat4::Scale(const Vec3& scale)
{
    *this = WithScale(scale);
    return *this;
}

Mat4& Mat4::Rotate(const float angle, const Vec3& axis)
{
    *this = WithRotation(angle, axis);
    return *this;
}

Mat4& Mat4::RotateDeg(const float angleDeg, const Vec3& axis)
{
    *this = WithRotationDeg(angleDeg, axis);
    return *this;
}

Mat4& Mat4::Rotate(const Vec3& eulerAngles)
{
    *this = WithRotation(eulerAngles);
    return *this;
}

Mat4& Mat4::RotateDeg(const Vec3& eulerAnglesDeg)
{
    *this = WithRotationDeg(eulerAnglesDeg);
    return *this;
}

Mat4& Mat4::Rotate(const Quat& quat)
{
    *this = WithRotation(quat);
    return *this;
}

Mat4 Mat4::WithTranslation(const Vec3& displacement) const
{
    return glm::translate(internal_mat, static_cast<glm::vec3>(displacement));
}

Mat4 Mat4::WithScale(const Vec3& scale) const
{
    return glm::scale(internal_mat, static_cast<glm::vec3>(scale));
}

Mat4 Mat4::WithRotation(const float angle, const Vec3& axis) const
{
    return glm::rotate(internal_mat, angle, static_cast<glm::vec3>(axis));
}

Mat4 Mat4::WithRotation(const Vec3& eulerAngles) const
{
    return *this * Quat::FromEulerAngles(eulerAngles).ToMatrix();
}

Mat4 Mat4::WithRotationDeg(const Vec3& eulerAnglesDeg) const
{
    return *this * Quat::FromEulerAnglesDeg(eulerAnglesDeg).ToMatrix();
}

Mat4 Mat4::WithRotation(const Quat& rotation) const
{
    return *this * rotation.ToMatrix();
}

Mat4 Mat4::WithInverse() const
{
    return Mat4(glm::inverse(internal_mat));
}

Mat4 Mat4::WithTranspose() const
{
    return Mat4(glm::transpose(internal_mat));
}

Mat4 Mat4::Hadamard(const Mat4& lhs, const Mat4& rhs)
{
    return Mat4(glm::matrixCompMult(lhs.internal_mat, rhs.internal_mat));
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::math
