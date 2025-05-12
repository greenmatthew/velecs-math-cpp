/// @file    Vec4.hpp
/// @author  Matthew Green
/// @date    2025-05-10 12:05:17
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/math/Consts.hpp"

#include <iostream>

#include <glm/vec4.hpp>

namespace velecs::math {

struct Vec2;
struct Vec3;

/// @struct Vec4
/// @brief Brief description.
///
/// Rest of description.
struct Vec4 {
public:
    // Enums

    // Public Fields

    static const Vec4 ZERO;         /// @brief A vector with all components set to zero (0, 0, 0, 0).
    static const Vec4 ORIGIN;       /// @brief A point representing the origin in homogeneous coordinates (0, 0, 0, 1).
    static const Vec4 ONE;          /// @brief A vector with all components set to one (1, 1, 1, 1).
    static const Vec4 NEG_ONE;      /// @brief A vector with all components set to negative one (-1, -1, -1, -1).
    static const Vec4 RIGHT;        /// @brief A vector representing the right direction (1, 0, 0, 0).
    static const Vec4 LEFT;         /// @brief A vector representing the left direction (-1, 0, 0, 0).
    static const Vec4 UP;           /// @brief A vector representing the up direction (0, 1, 0, 0).
    static const Vec4 DOWN;         /// @brief A vector representing the down direction (0, -1, 0, 0).
    static const Vec4 FORWARD;      /// @brief A vector representing the forward direction (0, 0, -1, 0).
    static const Vec4 BACKWARD;     /// @brief A vector representing the backward direction (0, 0, 1, 0).
    static const Vec4 POS_INFINITY; /// @brief A vector with all components set to positive infinity.
    static const Vec4 NEG_INFINITY; /// @brief A vector with all components set to negative infinity.
    static const Vec4 UNIT;         /// @brief A normalized vector with magnitude equal to 1. Derived from Vec4::ONE.
    static const Vec4 I;            /// @brief A unit vector along the x-axis (1, 0, 0, 0).
    static const Vec4 J;            /// @brief A unit vector along the y-axis (0, 1, 0, 0).
    static const Vec4 K;            /// @brief A unit vector along the z-axis (0, 0, 1, 0).
    static const Vec4 W;            /// @brief A unit vector along the w-axis (0, 0, 0, 1).
    

    float x; /// @brief The x-component of the vector.
    float y; /// @brief The y-component of the vector.
    float z; /// @brief The z-component of the vector.
    float w; /// @brief The w-component of the vector.

    // Constructors and Destructors
    
    /// @brief Constructs a Vec4 with specified x, y, and z components.
    /// @param[in] x The x-component.
    /// @param[in] y The y-component.
    /// @param[in] z The z-component.
    /// @param[in] w The w-component.
    inline Vec4(const float x, const float y, const float z, const float w)
        : x(x), y(y), z(z), w(w) {}

    /// @brief Copy constructor. Constructs a new Vec4 with the same values as the specified Vec4.
    /// @param[in] other The Vec4 to copy.
    inline Vec4(const Vec4& other)
        : x(other.x), y(other.y), z(other.z), w(other.w) {}

    /// @brief Constructs a Vec4 from a glm::vec4.
    /// @details Creates a Vec4 with components initialized from the given glm::vec4.
    /// @param[in] vec The glm::vec4 to convert from.
    inline Vec4(const glm::vec4& other)
        : x(other.x), y(other.y), z(other.z), w(other.w) {}



    /// @brief Constructs a Vec4 from a Vec2 with optional z and w components.
    /// @details The x and y components are initialized from the Vec2, while the z and w components 
    ///          are set to the specified values (defaulting to 0.0f).
    /// @param[in] vec2 The Vec2 from which to initialize the x and y components.
    /// @param[in] z The z-component, defaults to 0.0f.
    /// @param[in] w The w-component, defaults to 0.0f (creating a direction vector).
    Vec4(const Vec2 vec2, const float z = 0.0f, const float w = 0.0f);

    /// @brief Constructs a Vec4 with a specified x-component, a Vec2 for y and z, and an optional w-component.
    /// @details The x-component is set to the specified value, the y and z components are initialized 
    ///          from the Vec2, and w is set to the specified value.
    /// @param[in] x The x-component.
    /// @param[in] vec2 The Vec2 from which to initialize the y and z components.
    /// @param[in] w The w-component, defaults to 0.0f (creating a direction vector).
    Vec4(const float x, const Vec2 vec2, const float w = 0.0f);

    /// @brief Constructs a Vec4 with specified x and y components, and a Vec2 for the z and w components.
    /// @details The x and y components are set to the specified values, while the z and w components 
    ///          are initialized from the Vec2.
    /// @param[in] x The x-component.
    /// @param[in] y The y-component.
    /// @param[in] vec2 The Vec2 from which to initialize the z and w components.
    Vec4(const float x, const float y, const Vec2 vec2);



    /// @brief Constructs a Vec4 from a Vec3 and an optional w-component.
    /// @details Creates a Vec4 with its first three components (x,y,z) initialized from the Vec3,
    ///          and w set to the specified value. Default w=0 creates a direction vector.
    /// @param[in] vec3 The Vec3 from which to initialize the x, y, z components.
    /// @param[in] w The w-component, defaults to 0 for direction vectors (w=1 would create a point).
    Vec4(const Vec3 vec3, const float w = 0);

    /// @brief Constructs a Vec4 with a specified x-component and a Vec3 for the y, z, w components.
    /// @details The x-component is set to the specified value, while the y, z, and w components 
    ///          are initialized from the Vec3's x, y, and z values, respectively.
    /// @param[in] x The x-component of the new Vec4.
    /// @param[in] vec3 The Vec3 from which to initialize the y, z, and w components.
    Vec4(const float x, const Vec3 vec3);

    
    /// @brief Default destructor.
    ~Vec4() = default;

    // Public Methods

    /// @brief Converts the Vec4 to a glm::vec4.
    /// @returns A glm::vec4 with the same components as this Vec4.
    inline operator glm::vec4() const
    {
        return glm::vec4(x, y, z, w);
    }

    /// @brief Creates a point in homogeneous coordinates (w=1).
    /// @details This static factory method creates a Vec4 representing a point in 3D space
    ///          by setting the w-component to 1.0f.
    /// @param x The x-coordinate of the point.
    /// @param y The y-coordinate of the point.
    /// @param z The z-coordinate of the point.
    /// @returns A Vec4 representing a point with the given coordinates and w=1.0f.
    inline static Vec4 CreatePoint(const float x, const float y, const float z)
    {
        return Vec4(x, y, z, 1.0f);
    }

    /// @brief Creates a point in homogeneous coordinates (w=1) from a Vec3.
    /// @details This static factory method creates a Vec4 representing a point in 3D space
    ///          using the components from a Vec3 and setting the w-component to 1.0f.
    /// @param vec The Vec3 containing the x, y, and z coordinates of the point.
    /// @returns A Vec4 representing a point with the given coordinates and w=1.0f.
    static Vec4 CreatePoint(const Vec3 vec);

    /// @brief Creates a direction vector in homogeneous coordinates (w=0).
    /// @details This static factory method creates a Vec4 representing a direction vector
    ///          in 3D space by setting the w-component to 0.0f.
    /// @param x The x-component of the vector.
    /// @param y The y-component of the vector.
    /// @param z The z-component of the vector.
    /// @returns A Vec4 representing a direction vector with the given components and w=0.0f.
    inline static Vec4 CreateVector(const float x, const float y, const float z)
    {
        return Vec4(x, y, z, 0.0f);
    }

    /// @brief Creates a direction vector in homogeneous coordinates (w=0) from a Vec3.
    /// @details This static factory method creates a Vec4 representing a direction vector
    ///          in 3D space using the components from a Vec3 and setting the w-component to 0.0f.
    /// @param vec The Vec3 containing the x, y, and z components of the vector.
    /// @returns A Vec4 representing a direction vector with the given components and w=0.0f.
    static Vec4 CreateVector(const Vec3 vec);

    /// @brief Assigns the values of another Vec4 object to this Vec4 object.
    /// @param[in] other The other Vec4 object whose values will be assigned to this Vec4 object.
    /// @return A reference to this Vec4 object, after the assignment.
    inline Vec4& operator=(const Vec4 other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Checks if this Vec4 is equal to the specified Vec4.
    /// @param[in] other The Vec4 to compare with.
    /// @return True if the Vec4s are equal, false otherwise.
    inline bool operator==(const Vec4 other) const
    {
        return x == other.x &&
            y == other.y &&
            z == other.z &&
            w == other.w;
    }

    /// @brief Checks if this Vec4 is not equal to the specified Vec4.
    /// @param[in] other The Vec4 to compare with.
    /// @return True if the Vec4s are not equal, false otherwise.
    inline bool operator!=(const Vec4 other) const
    {
        return x != other.x ||
            y != other.y ||
            z != other.z ||
            w != other.w;
    }

    /// @brief Negates this Vec4.
    /// @return A new Vec4 that is the negation of this Vec4.
    inline Vec4 operator-() const
    {
        return Vec4(-x, -y, -z, -w);
    }

    /// @brief Overloads the addition assignment operator to add another Vec4 to this Vec4 and assign the result to this Vec4.
    /// @details This method adds the corresponding components of the other Vec4 to this Vec4 and assigns the result to this Vec4.
    /// @param[in] other The other Vec4 to add to this Vec4.
    /// @returns A reference to this Vec4 after the addition
    inline Vec4& operator+=(const Vec4 other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Overloads the subtraction assignment operator to subtract another Vec4 from this Vec4 and assign the result to this Vec4.
    /// @details This method subtracts the corresponding components of the other Vec4 from this Vec4 and assigns the result to this Vec4.
    /// @param[in] other The other Vec4 to subtract from this Vec4.
    /// @returns A reference to this Vec4 after the subtraction.
    inline Vec4& operator-=(const Vec4 other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Overloads the multiplication assignment operator to multiply this Vec4 by a scalar and assign the result to this Vec4.
    /// @details This method multiplies the components of this Vec4 by the specified scalar value and assigns the result to this Vec4.
    /// @param[in] scalar The scalar value to multiply this Vec4 by.
    /// @returns A reference to this Vec4 after the multiplication.
    inline Vec4& operator*=(const float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this; // Return ref to allow chaining assignment operations
    }

    /// @brief Overloads the division assignment operator to divide this Vec4 by a scalar and assign the result to this Vec4.
    /// @details This method divides the components of this Vec4 by the specified scalar value and assigns the result to this Vec4.
    /// @param[in] scalar The scalar value to divide this Vec4 by.
    /// @returns A reference to this Vec4 after the division.
    inline Vec4& operator/=(const float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this; // Return ref to allow chaining assignment operations
    }

    inline float& operator[](int index) {
        if (index >= 0 && index < 4) {
            return (&x)[index]; // Access array of 4 floats starting at address of x
        }
        throw std::out_of_range("Vec4 index out of range");
    }

    /// @brief Projects the homogeneous coordinates to 3D Cartesian coordinates.
    /// @details Performs homogeneous division, dividing x, y, and z by w.
    /// @returns A Vec3 containing the projected Cartesian coordinates.
    /// @throws std::runtime_error if w is zero (indicating a vector at infinity).
    Vec3 ToVec3() const;

    /// @brief Converts the homogeneous coordinates to 3D Cartesian coordinates without safety checks.
    /// @details Extracts just the xyz components without performing homogeneous division.
    /// @returns A Vec3 containing the xyz components.
    Vec3 XYZ() const;

    /// @brief Converts this Vec4 to a point (w=1) with the same effective spatial coordinates.
    /// @details If w is already non-zero, performs homogeneous division to normalize w to 1.
    ///          If w is zero, simply sets w to 1 without changing xyz (treating it as a direction).
    /// @returns A Vec4 representing a point with normalized homogeneous coordinates (w=1).
    Vec4 ToPoint() const;

    /// @brief Computes the L0 norm of this Vec4, which is the count of non-zero components.
    /// @returns The L0 norm.
    inline unsigned int L0Norm() const
    {
        return (x != 0 ? 1 : 0) + (y != 0 ? 1 : 0) + (z != 0 ? 1 : 0) + (w != 0 ? 1 : 0);
    }

    /// @brief Computes the L0 norm considering only the xyz components (for homogeneous coordinates).
    /// @returns The L0 norm of the spatial (xyz) components only.
    inline unsigned int L0NormSpatial() const
    {
        return (x != 0 ? 1 : 0) + (y != 0 ? 1 : 0) + (z != 0 ? 1 : 0);
    }

    /// @brief Computes the L1 norm of this Vec4, which is the sum of the absolute values of the components.
    /// @returns The L1 norm.
    inline float L1Norm() const
    {
        return std::abs(x) + std::abs(y) + std::abs(z) + std::abs(w);
    }

    /// @brief Computes the L1 norm considering only the xyz components (for homogeneous coordinates).
    /// @returns The sum of absolute values of the spatial (xyz) components only.
    inline float L1NormSpatial() const
    {
        return std::abs(x) + std::abs(y) + std::abs(z);
    }

    /// @brief Computes the L2 norm (magnitude) of this Vec4.
    /// @returns The L2 norm.
    inline float L2Norm() const
    {
        return std::sqrt(x*x + y*y + z*z + w*w);
    }

    /// @brief Computes the L2 norm considering only the xyz components (for homogeneous coordinates).
    /// @returns The square root of the sum of squares of the spatial (xyz) components only.
    inline float L2NormSpatial() const
    {
        return std::sqrt(x*x + y*y + z*z);
    }

    /// @brief Computes the L∞ norm (maximum absolute value) of this Vec4.
    /// @returns The maximum absolute value among all components.
    inline float LInfNorm() const
    {
        return std::max(std::max(std::max(std::abs(x), std::abs(y)), std::abs(z)), std::abs(w));
    }

    /// @brief Computes the L∞ norm considering only the xyz components (for homogeneous coordinates).
    /// @returns The maximum absolute value among the spatial (xyz) components only.
    inline float LInfNormSpatial() const
    {
        return std::max(std::max(std::abs(x), std::abs(y)), std::abs(z));
    }

    /// @brief Alias for L2Norm, computes the L2 norm (magnitude) of this Vec4.
    /// @returns The L2 norm.
    inline float Norm() const { return L2Norm(); }

    /// @brief Alias for L2Norm, computes the L2 norm (magnitude) of this Vec4.
    /// @returns The L2 norm.
    inline float Magnitude() const { return L2Norm(); }

    /// @brief Normalizes this Vec4, making its magnitude equal to 1.
    /// @returns The normalized Vec4.
    /// @note If the original magnitude is 0, returns the zero vector.
    Vec4 Normalize() const;

    /// @brief Projects the vector onto the i basis vector (x-axis).
    /// @returns The projection of the vector onto the i basis vector,
    /// resulting in a vector along the x-axis with the same x component as the original vector.
    inline Vec4 ProjOntoI() const
    {
        return Vec4(x, 0.0f, 0.0f, 0.0f);
    }

    /// @brief Projects the vector onto the j basis vector (y-axis).
    /// @returns The projection of the vector onto the j basis vector,
    /// resulting in a vector along the y-axis with the same y component as the original vector.
    inline Vec4 ProjOntoJ() const
    {
        return Vec4(0.0f, y, 0.0f, 0.0f);
    }

    /// @brief Projects the vector onto the k basis vector (z-axis).
    /// @returns The projection of the vector onto the k basis vector,
    /// resulting in a vector along the z-axis with the same z component as the original vector.
    inline Vec4 ProjOntoK() const
    {
        return Vec4(0.0f, 0.0f, z, 0.0f);
    }

    /// @brief Projects the vector onto the w basis vector (w-axis).
    /// @returns The projection of the vector onto the w basis vector,
    /// resulting in a vector along the w-axis with the same w component as the original vector.
    inline Vec4 ProjOntoW() const
    {
        return Vec4(0.0f, 0.0f, 0.0f, w);
    }

    /// @brief Computes the dot product of two Vec4 objects.
    /// @param a The first Vec4 object.
    /// @param b The second Vec4 object.
    /// @returns The dot product of a and b.
    inline static float Dot(const Vec4 a, const Vec4 b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    /// @brief Computes the 3D cross product of the spatial (xyz) components of two Vec4 objects.
    /// @details This performs the traditional 3D cross product on the xyz components and sets w=0.
    ///          The result is a direction vector perpendicular to the plane containing the spatial components
    ///          of the input vectors.
    /// @param a The first Vec4 object.
    /// @param b The second Vec4 object.
    /// @returns A Vec4 representing the cross product as a direction vector (w=0).
    static Vec4 Cross(const Vec4 a, const Vec4 b);

    /// @brief Computes the Hadamard product of two Vec4 objects.
    /// @param a The first Vec4 object.
    /// @param b The second Vec4 object.
    /// @returns The Hadamard product of a and b.
    inline static Vec4 Hadamard(const Vec4 a, const Vec4 b)
    {
        return Vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }

    /// @brief Alias for Hadamard, computes the element-wise multiplication of two Vec4s.
    /// @param a The first Vec4.
    /// @param b The second Vec4.
    /// @returns The element-wise multiplication of the two Vec4s.
    inline static Vec4 ElementwiseMultiply(const Vec4 a, const Vec4 b) { return Hadamard(a, b); }

    /// @brief Clamps the components of a Vec4 between the corresponding components of two other Vec4s.
    /// @param vec The Vec4 to clamp.
    /// @param min The Vec4 representing the minimum values.
    /// @param max The Vec4 representing the maximum values.
    /// @returns The clamped Vec4.
    static Vec4 Clamp(const Vec4 vec, const Vec4 min, const Vec4 max);

    /// @brief Computes a linear interpolation between two Vec4s.
    /// @param a The first Vec4.
    /// @param b The second Vec4.
    /// @param t The interpolation factor. A value of 0 returns a, and a value of 1 returns b.
    /// @returns The interpolated Vec4.
    inline static Vec4 Lerp(const Vec4 a, const Vec4 b, float t)
    {
        return Vec4
        (
            a.x + t * (b.x - a.x),
            a.y + t * (b.y - a.y),
            a.z + t * (b.z - a.z),
            a.w + t * (b.w - a.w)
        );
    }

    /// @brief Computes a linear interpolation between two points in homogeneous space.
    /// @details This performs a standard linear interpolation but ensures the result has w=1.
    ///          The inputs are assumed to already represent valid points.
    /// @param a The first point (assumed to have w=1).
    /// @param b The second point (assumed to have w=1).
    /// @param t The interpolation factor. A value of 0 returns a, and a value of 1 returns b.
    /// @returns The interpolated point with w=1.
    static Vec4 LerpPoints(const Vec4 a, const Vec4 b, float t);

    /// @brief Converts this Vec4 to a unit direction vector in the same direction.
    /// @details Creates a new Vec4 with w=0 and the spatial components (xyz) normalized.
    /// @returns A Vec4 in the same direction but with w=0 and xyz components normalized.
    /// @note If the original spatial magnitude is 0, returns the zero vector.
    Vec4 ToDirection() const;

    /// @brief Computes the angle between the spatial components of two vectors in radians.
    /// @details Calculates the angle between the xyz components, ignoring the w component.
    ///          This is appropriate for vectors representing directions in 3D space.
    /// @param a The first vector.
    /// @param b The second vector.
    /// @returns The angle between the spatial components in radians.
    static float SpatialAngle(const Vec4 a, const Vec4 b);

    /// @brief Computes the angle between the spatial components of two vectors in degrees.
    /// @details Calculates the angle between the xyz components, ignoring the w component.
    ///          This is appropriate for vectors representing directions in 3D space.
    /// @param a The first vector.
    /// @param b The second vector.
    /// @returns The angle between the spatial components in degrees.
    inline static float SpatialAngleDeg(const Vec4 a, const Vec4 b)
    {
        return SpatialAngle(a, b) * RAD_TO_DEG;  // convert radians to degrees
    }

    /// @brief Converts the Vec4 to a string representation.
    /// @returns A string representation of the Vec4.
    std::string ToString() const;

    /// @brief Outputs a Vec4 object to an output stream in a formatted manner.
    /// @param[in] os The output stream to write to.
    /// @param[in] vec The Vec4 object to output.
    /// @return The same output stream, for chaining.
    inline friend std::ostream& operator<<(std::ostream& os, const Vec4 vec)
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

/// @brief Overloads the addition operator to add two Vec4 objects together.
/// @details This method adds the corresponding components of the two Vec4 objects together.
/// @param[in] lhs The left-hand side Vec4 operand.
/// @param[in] rhs The right-hand side Vec4 operand.
/// @returns A new Vec4 object representing the sum of the two Vec4 operands.
inline Vec4 operator+(const Vec4 lhs, const Vec4 rhs)
{
    return Vec4{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
}

/// @brief Overloads the subtraction operator to subtract one Vec4 from another.
/// @details This method subtracts the corresponding components of the two Vec4 objects.
/// @param[in] lhs The left-hand side Vec4 operand.
/// @param[in] rhs The right-hand side Vec4 operand.
/// @returns A new Vec4 object representing the difference of the two Vec4 operands.
inline Vec4 operator-(const Vec4 lhs, const Vec4 rhs)
{
    return Vec4{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
}

/// @brief Overloads the multiplication operator to multiply a Vec4 object by a scalar value.
/// @details This method multiplies each component of the Vec4 object by the scalar value.
/// @param[in] lhs The Vec4 object to be multiplied.
/// @param[in] rhs The scalar value by which to multiply the Vec4 object.
/// @returns A new Vec4 object representing the product of the Vec4 object and the scalar value.
inline Vec4 operator*(const Vec4 lhs, const float rhs)
{
    return Vec4{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
}

/// @brief Overloads the division operator to divide a Vec4 by a scalar.
/// @details This method divides the components of the Vec4 by the specified scalar value.
/// @param[in] lhs The Vec4 operand.
/// @param[in] rhs The scalar operand.
/// @returns A new Vec4 object representing the quotient of the Vec4 and scalar operands.
inline Vec4 operator/(const Vec4 lhs, const float rhs)
{
    if (rhs == 0)
    {
        throw std::runtime_error("Division by zero error");
    }
    return Vec4{lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs};
}

/// @brief Overloads the multiplication operator to multiply a scalar value by a Vec4 object.
/// @details This method multiplies each component of the Vec4 object by the scalar value. 
/// This overload ensures that multiplication is commutative.
/// @param[in] lhs The scalar value by which to multiply the Vec4 object.
/// @param[in] rhs The Vec4 object to be multiplied.
/// @returns A new Vec4 object representing the product of the scalar value and the Vec4 object.
inline Vec4 operator*(const float lhs, const Vec4 rhs)
{
    return rhs * lhs;
}

} // namespace velecs::math
