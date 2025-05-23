/// @file    Vec3.cpp
/// @author  Matthew Green
/// @date    10/27/2023 17:23:08
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/math/Vec3.hpp"
#include "velecs/math/Vec2.hpp"

#include <sstream>
#include <algorithm>

namespace velecs::math {

// Public Fields

const Vec3 Vec3::ZERO         {  0.0f,  0.0f,  0.0f };
const Vec3 Vec3::ONE          {  1.0f,  1.0f,  1.0f };
const Vec3 Vec3::NEG_ONE      { -1.0f, -1.0f, -1.0f };
const Vec3 Vec3::RIGHT        {  1.0f,  0.0f,  0.0f };
const Vec3 Vec3::LEFT         { -1.0f,  0.0f,  0.0f };
const Vec3 Vec3::UP           {  0.0f,  1.0f,  0.0f };
const Vec3 Vec3::DOWN         {  0.0f, -1.0f,  0.0f };
const Vec3 Vec3::FORWARD      {  0.0f,  0.0f, -1.0f };
const Vec3 Vec3::BACKWARD     {  0.0f,  0.0f,  1.0f };
const Vec3 Vec3::POS_INFINITY { FLOAT_POS_INFINITY, FLOAT_POS_INFINITY, FLOAT_POS_INFINITY };
const Vec3 Vec3::NEG_INFINITY { FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY };
const Vec3 Vec3::UNIT         = ONE.Normalize();
const Vec3 Vec3::I            {  1.0f,  0.0f,  0.0f };
const Vec3 Vec3::J            {  0.0f,  1.0f,  0.0f };
const Vec3 Vec3::K            {  0.0f,  0.0f,  1.0f };

// Constructors and Destructors

Vec3::Vec3(const Vec2 vec2, const float z)
    : x(vec2.x), y(vec2.y), z(z) {}

Vec3::Vec3(const float x, const struct Vec2 vec2)
    : x(x), y(vec2.x), z(vec2.y) {}

// Public Methods

Vec3 Vec3::Normalize() const
{
    float magnitude = L2Norm();
    return (magnitude != 0) ? (*this)/magnitude : Vec3::ZERO;
}

Vec3 Vec3::Clamp(const Vec3 vec, const Vec3 min, const Vec3 max)
{
    return Vec3
    (
        std::clamp(vec.x, min.x, max.x),
        std::clamp(vec.y, min.y, max.y),
        std::clamp(vec.z, min.z, max.z)
    );
}

float Vec3::Angle(const Vec3 a, const Vec3 b)
{
    float dotProduct = Dot(a, b);
    float magnitudes = a.L2Norm() * b.L2Norm();
    if (magnitudes == 0) return 0;  // avoid division by zero
    float cosineTheta = dotProduct / magnitudes;
    // Clamp cosineTheta to the range [-1, 1] to avoid NaN due to floating point errors.
    cosineTheta = std::max(-1.0f, std::min(1.0f, cosineTheta));
    return std::acos(cosineTheta);  // result is in radians
}

std::string Vec3::ToString() const
{
    std::ostringstream oss;
    oss << '(' << x << ", " << y << ", " << z << ')';
    return oss.str();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::math
