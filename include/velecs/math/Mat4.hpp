/// @file    Mat4.hpp
/// @author  Matthew Green
/// @date    2025-05-09 17:32:52
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/math/Vec3.hpp"

#include <iostream>
#include <iomanip>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace velecs::math {

struct Vec4;

/// @struct Mat4
/// @brief A wrapper struct for glm::mat4 to provide consistent interfaces with other math classes.
///
/// This class wraps the glm::mat4 type to provide a consistent interface with other
/// classes in the velecs math library, while still allowing easy access to the
/// underlying glm functionality.
struct Mat4 {
public:
    // Enums

    // Public Fields

    static const Mat4 IDENTITY;     /// @brief A 4x4 identity matrix with ones on the main diagonal and zeros elsewhere.
    static const Mat4 ZERO;         /// @brief A 4x4 zero matrix with all elements set to zero.
    static const Mat4 NEG_IDENTITY; /// @brief A 4x4 negative identity matrix with -1 on the main diagonal.

    glm::mat4 internal_mat; /// @brief The internal GLM matrix.

    // Constructors and Destructors

    /// @brief Constructs a Mat4 from a glm::mat4.
    /// @param mat The glm::mat4 to initialize this Mat4 with.
    Mat4(const glm::mat4& mat);

    /// @brief Constructs a Mat4 with the specified value along the main diagonal.
    /// @param diagonal The value to place along the main diagonal of the matrix.
    Mat4(float diagonal);

    /// @brief Default deconstructor.
    ~Mat4() = default;

    // Public Methods

    /// @brief Overloads the multiplication assignment operator to multiply this matrix by another matrix.
    /// @details This method performs standard matrix multiplication and assigns the result to this matrix.
    /// @param[in] other The matrix to multiply with this matrix.
    /// @returns A reference to this matrix after the multiplication.
    Mat4& operator*=(const Mat4& other);

    /// @brief Performs component-wise multiplication of two matrices.
    /// @details Multiplies each component of lhs with the corresponding component of rhs.
    /// @param lhs The first matrix.
    /// @param rhs The second matrix.
    /// @returns A new matrix with each component being the product of the corresponding components.
    static inline Mat4 Hadamard(const Mat4& lhs, const Mat4& rhs)
    {
        return Mat4(glm::matrixCompMult(lhs.internal_mat, rhs.internal_mat));
    }

    /// @brief Returns a new matrix with translation applied to this matrix.
    /// @param translation The translation vector to apply.
    /// @return A new matrix representing this matrix with the translation applied.
    Mat4 Translated(const Vec3& translation) const;

    /// @brief Returns a new matrix with scaling applied to this matrix.
    /// @param scale The scale factors for x, y, and z axes.
    /// @return A new matrix representing this matrix with the scaling applied.
    Mat4 Scaled(const Vec3& scale) const;

    /// @brief Returns a new matrix with rotation applied to this matrix.
    /// @param rad The rotation angle in radians.
    /// @param axis The axis to rotate around (should be normalized).
    /// @return A new matrix representing this matrix with the rotation applied.
    Mat4 Rotated(const float rad, const Vec3& axis) const;

    /// @brief Gets the X basis vector (first column) of the matrix.
    /// @details Returns the x-axis basis vector which represents the 
    ///          right direction in the matrix's transformation.
    /// @returns A Vec4 containing the first column of the matrix.
    Vec4 XBasis() const;

    /// @brief Gets the Y basis vector (second column) of the matrix.
    /// @details Returns the y-axis basis vector which represents the 
    ///          up direction in the matrix's transformation.
    /// @returns A Vec4 containing the second column of the matrix.
    Vec4 YBasis() const;

    /// @brief Gets the Z basis vector (third column) of the matrix.
    /// @details Returns the z-axis basis vector which represents the 
    ///          forward direction in the matrix's transformation.
    /// @returns A Vec4 containing the third column of the matrix.
    Vec4 ZBasis() const;

    /// @brief Gets the translation vector (fourth column) of the matrix.
    /// @details Returns the translation component of the transformation matrix,
    ///          representing the position in world space.
    /// @returns A Vec4 containing the fourth column of the matrix.
    Vec4 Translation() const;

    /// @brief Alias for Translation(). Gets the position vector from the matrix.
    /// @returns A Vec4 containing the translation/position component.
    inline Vec4 Position() const { return Translation(); }

    /// @brief Creates a translation matrix from a Vec3.
    /// @param translation The translation vector to use.
    /// @return A new transformation matrix with the specified translation applied to an identity matrix.
    static inline Mat4 CreateTranslation(const Vec3& translation)
    {
        return glm::translate(glm::mat4(1.0f), static_cast<glm::vec3>(translation));
    }

    /// @brief Creates a scaling matrix from a Vec3.
    /// @param scale The scale factors for x, y, and z axes.
    /// @return A new transformation matrix with the specified scaling applied to an identity matrix.
    static inline Mat4 CreateScale(const Vec3& scale)
    {
        return glm::scale(glm::mat4(1.0f), static_cast<glm::vec3>(scale));
    }

    /// @brief Creates a rotation matrix around an arbitrary axis.
    /// @param rad The rotation angle in radians.
    /// @param axis The axis to rotate around (should be normalized).
    /// @return A new transformation matrix with the specified rotation applied to an identity matrix.
    static inline Mat4 CreateRotation(const float rad, const Vec3& axis)
    {
        return glm::rotate(glm::mat4(1.0f), rad, static_cast<glm::vec3>(axis));
    }

    /// @brief Outputs a Mat4 object to an output stream in a formatted manner.
    /// @param[in] os The output stream to write to.
    /// @param[in] mat The Mat4 object to output.
    /// @return The same output stream, for chaining.
    friend std::ostream& operator<<(std::ostream& os, const Mat4& mat)
    {
        for (int row = 0; row < 4; ++row) {
            os << "| ";
            for (int col = 0; col < 4; ++col) {
                os << std::setw(10) << std::setprecision(4) << mat.internal_mat[col][row] << " ";
            }
            os << "|" << std::endl;
        }
        return os;
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

/// @brief Overloads the multiplication operator to multiply two matrices.
/// @details Performs standard matrix multiplication (not component-wise).
/// @param[in] lhs The left-hand side matrix operand.
/// @param[in] rhs The right-hand side matrix operand.
/// @returns A new matrix representing the matrix product of lhs and rhs.
inline Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
{
    return Mat4(lhs.internal_mat * rhs.internal_mat);
}

} // namespace velecs::math
