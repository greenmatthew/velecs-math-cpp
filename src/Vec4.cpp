/// @file    Vec4.cpp
/// @author  Matthew Green
/// @date    2025-05-10 12:26:03
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/math/Vec4.hpp"
#include "velecs/math/Vec3.hpp"
#include "velecs/math/Vec2.hpp"

#include <sstream>
#include <algorithm>

namespace velecs::math {

// Public Fields

const Vec4 Vec4::ZERO         {  0.0f,  0.0f,  0.0f,  0.0f  };
const Vec4 Vec4::ORIGIN       {  0.0f,  0.0f,  0.0f,  1.0f  };
const Vec4 Vec4::ONE          {  1.0f,  1.0f,  1.0f,  1.0f  };
const Vec4 Vec4::NEG_ONE      { -1.0f, -1.0f, -1.0f, -1.0f  };
const Vec4 Vec4::RIGHT        {  1.0f,  0.0f,  0.0f,  0.0f  };
const Vec4 Vec4::LEFT         { -1.0f,  0.0f,  0.0f,  0.0f  };
const Vec4 Vec4::UP           {  0.0f,  1.0f,  0.0f,  0.0f  };
const Vec4 Vec4::DOWN         {  0.0f, -1.0f,  0.0f,  0.0f  };
const Vec4 Vec4::FORWARD      {  0.0f,  0.0f, -1.0f,  0.0f  };
const Vec4 Vec4::BACKWARD     {  0.0f,  0.0f,  1.0f,  0.0f  };
const Vec4 Vec4::POS_INFINITY { FLOAT_POS_INFINITY, FLOAT_POS_INFINITY, FLOAT_POS_INFINITY, FLOAT_POS_INFINITY };
const Vec4 Vec4::NEG_INFINITY { FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY };
const Vec4 Vec4::UNIT         = ONE.Normalize();
const Vec4 Vec4::I            {  1.0f,  0.0f,  0.0f,  0.0f };
const Vec4 Vec4::J            {  0.0f,  1.0f,  0.0f,  0.0f };
const Vec4 Vec4::K            {  0.0f,  0.0f,  1.0f,  0.0f };
const Vec4 Vec4::W            {  0.0f,  0.0f,  0.0f,  1.0f };

// Constructors and Destructors

Vec4::Vec4(const Vec2 vec2, const float z, const float w)
    : x(vec2.x), y(vec2.y), z(z), w(w) {}

Vec4::Vec4(const float x, const Vec2 vec2, const float w)
    : x(x), y(vec2.x), z(vec2.y), w(w) {}

Vec4::Vec4(const float x, const float y, const Vec2 vec2)
    : x(x), y(y), z(vec2.x), w(vec2.y) {}



Vec4::Vec4(const Vec3 vec3, const float w)
    : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}

Vec4::Vec4(const float x, const Vec3 vec3)
    : x(x), y(vec3.x), z(vec3.y), w(vec3.z) {}

// Public Methods

Vec4 Vec4::CreatePoint(const Vec3 vec)
{
    return Vec4(vec, 1.0f);
}

Vec4 Vec4::CreateVector(const Vec3 vec)
{
    return Vec4(vec, 0.0f);
}

Vec3 Vec4::ToVec3() const
{
    if (w == 0.0f) {
        throw std::runtime_error("Cannot project a Vec4 with w=0 to Vec3 (division by zero)");
    }
    
    float invW = 1.0f / w;
    return Vec3(x * invW, y * invW, z * invW);
}

Vec3 Vec4::XYZ() const
{
    return Vec3(x, y, z);
}

Vec4 Vec4::ToPoint() const
{
    if (std::abs(w) < 1e-6f) {
        // If w is essentially zero, we're dealing with a direction vector
        // Just set w to 1 without changing xyz
        return Vec4(x, y, z, 1.0f);
    } else {
        // Perform homogeneous division to normalize w to 1
        float invW = 1.0f / w;
        return Vec4(x * invW, y * invW, z * invW, 1.0f);
    }
}

Vec4 Vec4::Normalize() const
{
    float magnitude = L2Norm();
    return (magnitude != 0) ? (*this)/magnitude : Vec4::ZERO;
}

Vec4 Vec4::Cross(const Vec4 a, const Vec4 b)
{
    // Compute 3D cross product and set w=0 (making it a direction vector)
    return Vec4
    (
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
        0.0f  // Set w=0 to indicate a direction vector
    );
}

Vec4 Vec4::Clamp(const Vec4 vec, const Vec4 min, const Vec4 max)
{
    return Vec4
    (
        std::clamp(vec.x, min.x, max.x),
        std::clamp(vec.y, min.y, max.y),
        std::clamp(vec.z, min.z, max.z),
        std::clamp(vec.w, min.w, max.w)
    );
}

Vec4 Vec4::LerpPoints(const Vec4 a, const Vec4 b, float t)
{
    // Assert that inputs are valid points (w≈1)
    assert(std::abs(a.w - 1.0f) < 1e-6f && "First input to LerpPoints must be a point (w=1)");
    assert(std::abs(b.w - 1.0f) < 1e-6f && "Second input to LerpPoints must be a point (w=1)");
    
    // Standard linear interpolation, preserving w=1
    return Vec4(
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        a.z + t * (b.z - a.z),
        1.0f  // Force w=1 for the result
    );
}

Vec4 Vec4::ToDirection() const
{
    float spatialMagnitude = std::sqrt(x*x + y*y + z*z);
    
    if (spatialMagnitude < 1e-6f) {
        return Vec4::ZERO; // Return zero vector if spatial components are essentially zero
    }
    
    float invMag = 1.0f / spatialMagnitude;
    return Vec4(x * invMag, y * invMag, z * invMag, 0.0f);
}

float Vec4::SpatialAngle(const Vec4 a, const Vec4 b)
{
    // Compute dot product of spatial components only
    float dotProduct = a.x * b.x + a.y * b.y + a.z * b.z;
    
    // Compute magnitudes of spatial components only
    float magA = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    float magB = std::sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
    
    float magnitudes = magA * magB;
    if (magnitudes < 1e-6f) return 0.0f;  // avoid division by zero
    
    float cosineTheta = dotProduct / magnitudes;
    // Clamp cosineTheta to the range [-1, 1] to avoid NaN due to floating point errors.
    cosineTheta = std::max(-1.0f, std::min(1.0f, cosineTheta));
    return std::acos(cosineTheta);  // result is in radians
}

std::string Vec4::ToString() const
{
    std::ostringstream oss;
    oss << '(' << x << ", " << y << ", " << z << ", " << w << ')';
    return oss.str();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::math
