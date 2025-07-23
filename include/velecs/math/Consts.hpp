/// @file    Consts.h
/// @author  Matthew Green
/// @date    10/15/2023 12:36:20
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <limits>

namespace velecs::math {

constexpr float PI = 0x1.921fb54442d18p1f; /// @brief The mathematical constant Pi (π).
constexpr float TWO_PI = 2.0f * PI; /// @brief The mathematical constant Pi (π).

constexpr double PI_D = 0x1.921fb54442d18p1;
constexpr double TWO_PI_D = 2.0 * PI_D;

constexpr float DEG_TO_RAD = PI / 180.0f; /// @brief Conversion factor to convert degrees to radians.
constexpr float RAD_TO_DEG = 180.0f / PI; /// @brief Conversion factor to convert radians to degrees.

constexpr float FLOAT_POS_INFINITY = std::numeric_limits<float>::infinity(); /// @brief Representation of positive infinity in floating-point.
constexpr float FLOAT_NEG_INFINITY = -FLOAT_POS_INFINITY; /// @brief Representation of negative infinity in floating-point.
constexpr float FLOAT_MAX_VALUE = std::numeric_limits<float>::max();
constexpr float FLOAT_MIN_VALUE = std::numeric_limits<float>::min();

} // namespace velecs::math
