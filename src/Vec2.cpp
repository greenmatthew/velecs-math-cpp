/// @file    Vec2.cpp
/// @author  Matthew Green
/// @date    10/15/2023 12:36:20
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/math/Vec2.hpp"
#include "velecs/math/Vec3.hpp"

#include <sstream>
#include <algorithm>

namespace velecs::math {

// Public Fields

const Vec2 Vec2::ZERO         {  0.0f,  0.0f };
const Vec2 Vec2::ONE          {  1.0f,  1.0f };
const Vec2 Vec2::NEG_ONE      { -1.0f, -1.0f };
const Vec2 Vec2::UP           {  0.0f, -1.0f };
const Vec2 Vec2::DOWN         {  0.0f,  1.0f };
const Vec2 Vec2::RIGHT        {  1.0f,  0.0f };
const Vec2 Vec2::LEFT         { -1.0f,  0.0f };
const Vec2 Vec2::POS_INFINITY { FLOAT_POS_INFINITY, FLOAT_POS_INFINITY };
const Vec2 Vec2::NEG_INFINITY { FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY };
const Vec2 Vec2::UNIT         = ONE.Normalize();
const Vec2 Vec2::I            {  1.0f,  0.0f };
const Vec2 Vec2::J            {  0.0f,  1.0f };

// Constructors and Destructors

// Public Methods

Vec2 Vec2::Normalize() const
{
    float magnitude = L2Norm();
    return (magnitude != 0) ? (*this)/magnitude : Vec2::ZERO;
}

Vec2 Vec2::Clamp(const Vec2 vec, const Vec2 min, const Vec2 max)
{
    return Vec2
    (
        std::clamp(vec.x, min.x, max.x),
        std::clamp(vec.y, min.y, max.y)
    );
}

float Vec2::Angle(const Vec2 a, const Vec2 b)
{
    float dotProduct = Dot(a, b);
    float magnitudes = a.L2Norm() * b.L2Norm();
    if (magnitudes == 0) return 0;  // avoid division by zero
    float cosineTheta = dotProduct / magnitudes;
    return std::acos(cosineTheta);  // result is in radians
}

std::string Vec2::ToString() const
{
    std::ostringstream oss;
    oss << '(' << x << ", " << y << ')';
    return oss.str();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::math
