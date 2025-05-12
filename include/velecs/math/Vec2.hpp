/// @file    Vec2.h
/// @author  Matthew Green
/// @date    10/15/2023 12:36:20
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/math/Consts.hpp"

#include <string>
#include <ostream>

#include <glm/vec2.hpp>

namespace velecs::math {

struct Vec3;

/// @struct Vec2
/// @brief A 2D vector structure for representing points or vectors in 2D space.
struct Vec2
{
public:
    // Enums

    // Public Fields

    static const Vec2 ZERO;         /// @brief A vector with all components set to zero (0, 0).
    static const Vec2 ONE;          /// @brief A vector with all components set to one (1, 1).
    static const Vec2 NEG_ONE;      /// @brief A vector with all components set to negative one (-1, -1).
    static const Vec2 UP;           /// @brief A vector representing the up direction in the application's coordinate system (0, -1).
    static const Vec2 DOWN;         /// @brief A vector representing the down direction in the application's coordinate system (0, 1).
    static const Vec2 RIGHT;        /// @brief A vector representing the right direction along the x-axis (1, 0).
    static const Vec2 LEFT;         /// @brief A vector representing the left direction along the x-axis (-1, 0).
    static const Vec2 POS_INFINITY; /// @brief A vector with all components set to positive infinity.
    static const Vec2 NEG_INFINITY; /// @brief A vector with all components set to negative infinity.
    static const Vec2 UNIT;         /// @brief A normalized vector with magnitude equal to 1, derived from Vec2::ONE.
    static const Vec2 I;            /// @brief A unit vector along the x-axis (1, 0).
    static const Vec2 J;            /// @brief A unit vector along the y-axis (0, 1).


    float x;  /// @brief The x-component of the vector.
    float y;  /// @brief The y-component of the vector.

    // Constructors and Destructors

    /// @brief Constructs a Vec2 with the specified coordinates.
    /// @param[in] x The x-coordinate.
    /// @param[in] y The y-coordinate.
    inline Vec2(const float x, const float y)
        : x(x), y(y) {}

    /// @brief Copy constructor. Constructs a new Vec2 with the same values as the specified Vec2.
    /// @param[in] other The Vec2 to copy.
    inline Vec2(const Vec2 &other)
        : x(other.x), y(other.y) {}
    
    /// @brief Constructs a Vec2 from a glm::vec2.
    /// @details Creates a new Vec2 object with components initialized from the given glm::vec2.
    ///          This allows for easy conversion from GLM's vector type to the velecs math library.
    /// @param[in] other The glm::vec2 to copy components from.
    inline Vec2(const glm::vec2 &other)
        : x(other.x), y(other.y) {}

    /// @brief Default deconstructor.
    ~Vec2() = default;
    
    // Public Methods

    /// @brief Converts the Vec2 to a glm::vec2.
    /// @returns A glm::vec2 with the same components as this Vec2.
    inline operator glm::vec2() const
    {
        return glm::vec2(x, y);
    }

    /// @brief Assigns the values of another Vec2 object to this Vec2 object.
    /// @param[in] other The other Vec2 object whose values will be assigned to this Vec2 object.
    /// @return A reference to this Vec2 object, after the assignment.
    inline Vec2& operator=(const Vec2 other)
    {
        x = other.x;
        y = other.y;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Checks if this Vec2 is equal to the specified Vec2.
    /// @param[in] other The Vec2 to compare with.
    /// @return True if the Vec2s are equal, false otherwise.
    inline bool operator==(const Vec2 other) const
    {
        return x == other.x &&
            y == other.y;
    }

    /// @brief Checks if this Vec2 is not equal to the specified Vec2.
    /// @param[in] other The Vec2 to compare with.
    /// @return True if the Vec2s are not equal, false otherwise.
    inline bool operator!=(const Vec2 other) const
    {
        return x != other.x ||
            y != other.y;
    }

    /// @brief Negates this Vec2 object, producing a new Vec2 object with the negated values.
    /// @return A new Vec2 object with the negated values of this Vec2 object.
    inline Vec2 operator-() const
    {
        return Vec2(-x, -y);
    }

    /// @brief Adds another Vec2 to this Vec2 and assigns the result to this Vec2.
    /// @param[in] other The other Vec2.
    /// @return A reference to this Vec2.
    inline Vec2& operator+=(const Vec2 other)
    {
        x += other.x;
        y += other.y;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Subtracts another Vec2 from this Vec2 and assigns the result to this Vec2.
    /// @param[in] other The other Vec2.
    /// @return A reference to this Vec2.
    inline Vec2& operator-=(const Vec2 other)
    {
        x -= other.x;
        y -= other.y;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Multiplies this Vec2 by a scalar and assigns the result to this Vec2.
    /// @param[in] scalar The scalar value.
    /// @return A reference to this Vec2.
    inline Vec2& operator*=(const float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Divides this Vec2 by a scalar and assigns the result to this Vec2.
    /// @param[in] scalar The scalar value.
    /// @return A reference to this Vec2.
    inline Vec2& operator/=(const float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Provides array-like access to vector components.
    /// @details Allows accessing vector components by index, where [0]=x, [1]=y.
    ///          Includes bounds checking to prevent invalid memory access.
    /// @param index The index of the component to access (0-1).
    /// @returns A reference to the component at the specified index.
    /// @throws std::out_of_range if the index is out of bounds (not 0-1).
    inline float& operator[](int index)
    {
        if (index >= 0 && index < 2) {
            return (&x)[index]; // Access array of 2 floats starting at address of x
        }
        throw std::out_of_range("Vec2 index out of range");
    }

    /// @brief Provides const array-like access to vector components.
    /// @details Allows read-only access to vector components by index, where [0]=x, [1]=y.
    ///          Includes bounds checking to prevent invalid memory access.
    /// @param index The index of the component to access (0-1).
    /// @returns A const reference to the component at the specified index.
    /// @throws std::out_of_range if the index is out of bounds (not 0-1).
    inline const float& operator[](int index) const
    {
        if (index >= 0 && index < 2) {
            return (&x)[index]; // Access array of 2 floats starting at address of x
        }
        throw std::out_of_range("Vec2 index out of range");
    }

    /// @brief Computes the L0 norm of this Vec2, which is the count of non-zero components.
    /// @returns The L0 norm.
    inline unsigned int L0Norm() const
    {
        return (x != 0 ? 1 : 0) + (y != 0 ? 1 : 0);
    }

    /// @brief Computes the L1 norm of this Vec2, which is the sum of the absolute values of the components.
    /// @returns The L1 norm.
    inline float L1Norm() const
    {
        return std::abs(x) + std::abs(y);
    }

    /// @brief Computes the L2 norm (magnitude) of this Vec2.
    /// @returns The L2 norm.
    inline float L2Norm() const
    {
        return sqrt(x * x + y * y);
    }

    /// @brief Computes the L∞ norm (maximum absolute value) of this Vec2.
    /// @details The L∞ norm is the maximum absolute value among all components.
    /// @returns The maximum absolute value of any component.
    inline float LInfNorm() const
    {
        return std::max(std::abs(x), std::abs(y));
    }

    /// @brief Alias for L2Norm, computes the L2 norm (magnitude) of this Vec2.
    /// @returns The L2 norm.
    inline float Norm() const { return L2Norm(); }

    /// @brief Alias for L2Norm, computes the L2 norm (magnitude) of this Vec2.
    /// @returns The L2 norm.
    inline float Magnitude() const { return L2Norm(); }

    /// @brief Normalizes this Vec2, making its magnitude equal to 1.
    /// @returns The normalized Vec2.
    Vec2 Normalize() const;

    /// @brief Projects the vector onto the i basis vector (x-axis).
    /// @returns The projection of the vector onto the i basis vector.
    inline Vec2 ProjOntoI() const
    {
        return Vec2(this->x, 0.0f);
    }

    /// @brief Projects the vector onto the j basis vector (y-axis).
    /// @returns The projection of the vector onto the j basis vector.
    inline Vec2 ProjOntoJ() const
    {
        return Vec2(0.0f, this->y);
    }

    /// @brief Computes the dot product of two Vec2 objects.
    /// @param a The first Vec2 object.
    /// @param b The second Vec2 object.
    /// @returns The dot product of a and b.
    inline static float Dot(const Vec2 a, const Vec2 b)
    {
        return a.x * b.x + a.y * b.y;
    }

    /// @brief Computes the cross product of two Vec2 objects.
    /// @param a The first Vec2 object.
    /// @param b The second Vec2 object.
    /// @returns The cross product of a and b.
    inline static float Cross(const Vec2 a, const Vec2 b)
    {
        return a.x * b.y - a.y * b.x;
    }

    /// @brief Computes the Hadamard product of two Vec2 objects.
    /// @param a The first Vec2 object.
    /// @param b The second Vec2 object.
    /// @returns The Hadamard product of a and b.
    inline static Vec2 Hadamard(const Vec2 a, const Vec2 b)
    {
        return Vec2(a.x * b.x, a.y * b.y);
    }

    /// @brief Alias for Hadamard, computes the element-wise multiplication of two Vec2s.
    /// @param a The first Vec2.
    /// @param b The second Vec2.
    /// @returns The element-wise multiplication of the two Vec2s.
    inline static Vec2 ElementwiseMultiply(const Vec2 a, const Vec2 b) { return Hadamard(a, b); }

    /// @brief Clamps the components of a Vec2 between the corresponding components of two other Vec2s.
    /// @param vec The Vec2 to clamp.
    /// @param min The Vec2 representing the minimum values.
    /// @param max The Vec2 representing the maximum values.
    /// @returns The clamped Vec2.
    static Vec2 Clamp(const Vec2 vec, const Vec2 min, const Vec2 max);

    /// @brief Computes a linear interpolation between two Vec2s.
    /// @param a The first Vec2.
    /// @param b The second Vec2.
    /// @param t The interpolation factor. A value of 0 returns a, and a value of 1 returns b.
    /// @returns The interpolated Vec2.
    inline static Vec2 Lerp(const Vec2 a, const Vec2 b, float t)
    {
        return Vec2
        (
            a.x + t * (b.x - a.x),
            a.y + t * (b.y - a.y)
        );
    }

    /// @brief Computes the angle between two vectors in radians.
    /// @param a The first vector.
    /// @param b The second vector.
    /// @returns The angle between the vectors in radians.
    static float Angle(const Vec2 a, const Vec2 b);

    /// @brief Computes the angle between two vectors in degrees.
    /// @param a The first vector.
    /// @param b The second vector.
    /// @returns The angle between the vectors in degrees.
    inline static float AngleDeg(const Vec2 a, const Vec2 b)
    {
        return Angle(a, b) * RAD_TO_DEG;  // convert radians to degrees
    }

    /// @brief Converts the Vec2 to a string representation.
    /// @returns A string representation of the Vec2.
    std::string ToString() const;

    /// @brief Outputs a Vec2 object to an output stream in a formatted manner.
    /// @param[in] os The output stream to write to.
    /// @param[in] vec The Vec2 object to output.
    /// @return The same output stream, for chaining.
    inline friend std::ostream& operator<<(std::ostream& os, const Vec2 vec)
    {
        os << vec.ToString();
        return os;
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

/// @brief Adds two Vec2 vectors.
/// @param[in] lhs The first Vec2 operand.
/// @param[in] rhs The second Vec2 operand.
/// @return A new Vec2 that is the sum of the two Vec2 operands.
inline Vec2 operator+(const Vec2 lhs, const Vec2 rhs)
{
    return Vec2{lhs.x + rhs.x, lhs.y + rhs.y};
}

/// @brief Subtracts one Vec2 from another.
/// @param[in] lhs The Vec2 to subtract from.
/// @param[in] rhs The Vec2 to be subtracted.
/// @return A new Vec2 that is the difference of the two Vec2 operands.
inline Vec2 operator-(const Vec2 lhs, const Vec2 rhs)
{
    return Vec2{lhs.x - rhs.x, lhs.y - rhs.y};
}

/// @brief Multiplies a Vec2 vector by a scalar.
/// @param[in] lhs The Vec2 operand.
/// @param[in] rhs The scalar value to multiply with.
/// @return A new Vec2 that is the product of the Vec2 and the scalar.
inline Vec2 operator*(const Vec2 lhs, const float rhs)
{
    return Vec2{lhs.x * rhs, lhs.y * rhs};
}

/// @brief Divides a Vec2 vector by a scalar.
/// @param[in] lhs The Vec2 operand.
/// @param[in] rhs The scalar value to divide by.
/// @return A new Vec2 that is the quotient of the Vec2 divided by the scalar.
inline Vec2 operator/(const Vec2 lhs, const float rhs)
{
    if (rhs == 0)
    {
        throw std::runtime_error("Division by zero error");
    }
    return Vec2{lhs.x / rhs, lhs.y / rhs};
}

/// @brief Multiplies a scalar value by a Vec2 vector.
/// @param[in] lhs The scalar value.
/// @param[in] rhs The Vec2 operand.
/// @return The product of the scalar value and the Vec2.
inline Vec2 operator*(const float lhs, const Vec2 rhs)
{
    return rhs * lhs;
}

} // namespace velecs::math
