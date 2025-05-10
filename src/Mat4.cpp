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
#include "velecs/math/Vec4.hpp"

namespace velecs::math {

// Public Fields

const Mat4 Mat4::IDENTITY = glm::mat4(1.0f);
const Mat4 Mat4::ZERO = glm::mat4(0.0f);
const Mat4 Mat4::NEG_IDENTITY = glm::mat4(-1.0f);

// Constructors and Destructors

Mat4::Mat4(const glm::mat4& mat)
    : internal_mat(mat) {}

Mat4::Mat4(float diagonal)
    : internal_mat(glm::mat4(diagonal)) {}

// Public Methods

Mat4& Mat4::operator*=(const Mat4& other)
{
    internal_mat = internal_mat * other.internal_mat;
    return *this; // Return ref to allow chaining assignment operations
}

Mat4 Mat4::Translated(const Vec3& translation) const
{
    return glm::translate(internal_mat, static_cast<glm::vec3>(translation));
}

Mat4 Mat4::Scaled(const Vec3& scale) const
{
    return glm::scale(internal_mat, static_cast<glm::vec3>(scale));
}

Mat4 Mat4::Rotated(const float rad, const Vec3& axis) const
{
    return glm::rotate(internal_mat, rad, static_cast<glm::vec3>(axis));
}

Vec4 Mat4::XBasis() const
{
    auto column = internal_mat[0];
    return Vec4{ column[0], column[1], column[2], column[3] };
}

Vec4 Mat4::YBasis() const
{
    auto column = internal_mat[1];
    return Vec4{ column[0], column[1], column[2], column[3] };
}

Vec4 Mat4::ZBasis() const
{
    auto column = internal_mat[2];
    return Vec4{ column[0], column[1], column[2], column[3] };
}

Vec4 Mat4::Translation() const
{
    auto column = internal_mat[3];
    return Vec4{ column[0], column[1], column[2], column[3] };
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::math
