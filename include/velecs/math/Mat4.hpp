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

#include "velecs/math/Consts.hpp"
#include "velecs/math/Vec4.hpp"

#include <iostream>
#include <iomanip>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace velecs::math {

struct Vec3;
struct Quat;

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
    inline Mat4(const glm::mat4& mat)
        : internal_mat(mat) {}

    /// @brief Constructs a Mat4 with the specified value along the main diagonal.
    /// @param diagonal The value to place along the main diagonal of the matrix.
    Mat4(float diagonal);

    /// @brief Default deconstructor.
    ~Mat4() = default;

    // Public Methods

    /// @brief Creates a transformation matrix from a position vector.
    /// @details Efficiently constructs a translation matrix by directly setting the
    ///          position components in the last column of the identity matrix.
    /// @param position The position vector to use for translation.
    /// @return A transformation matrix representing translation to the specified position.
    static Mat4 FromPosition(const Vec3& position);

    /// @brief Creates a transformation matrix from scale factors.
    /// @details Efficiently constructs a scaling matrix by directly setting the
    ///          scale components along the main diagonal of the identity matrix.
    /// @param scale The scale factors for the x, y, and z axes.
    /// @return A transformation matrix representing scaling by the specified factors.
    static Mat4 FromScale(const Vec3& scale);

    /// @brief Creates a rotation matrix from Euler angles in radians.
    /// @details Converts the Euler angles to a quaternion and then to a rotation matrix.
    ///          Uses the order X-Y-Z for applying rotations (pitch, yaw, roll).
    /// @param rotation The rotation vector in radians (x=pitch, y=yaw, z=roll).
    /// @return A transformation matrix representing the specified rotation.
    static Mat4 FromRotation(const Vec3& rotation);

    /// @brief Creates a rotation matrix from Euler angles in degrees.
    /// @details Converts the Euler angles to a quaternion and then to a rotation matrix.
    ///          Uses the order X-Y-Z for applying rotations (pitch, yaw, roll).
    ///          This is a convenience function that first converts degrees to radians.
    /// @param rotationDeg The rotation vector in degrees (x=pitch, y=yaw, z=roll).
    /// @return A transformation matrix representing the specified rotation.
    static Mat4 FromRotationDeg(const Vec3& rotationDeg);

        /// @brief Creates a perspective projection matrix suitable for Vulkan rendering
    /// @details This method builds a perspective projection matrix that accounts for Vulkan's coordinate
    ///          system conventions, with Y pointing down and Z in [0,1] range. It applies the necessary
    ///          coordinate system transformation to match Vulkan's expectations.
    /// @param verticalFov The vertical field of view in degrees
    /// @param aspectRatio The aspect ratio (width/height) of the viewport
    /// @param nearPlane The distance to the near clipping plane (must be positive)
    /// @param farPlane The distance to the far clipping plane (must be greater than near plane)
    /// @return A perspective projection matrix compatible with Vulkan's coordinate system
    static Mat4 FromPerspective(float verticalFov, float aspectRatio, float nearPlane, float farPlane);

    /// @brief Creates an orthographic projection matrix suitable for Vulkan rendering
    /// @details This method builds an orthographic projection matrix that maps the specified view volume
    ///          to Vulkan's normalized device coordinates, accounting for Vulkan's coordinate system
    ///          with Y pointing down and Z in [0,1] range.
    /// @param left The left coordinate of the view volume
    /// @param right The right coordinate of the view volume
    /// @param bottom The bottom coordinate of the view volume
    /// @param top The top coordinate of the view volume
    /// @param nearPlane The near clipping plane distance
    /// @param farPlane The far clipping plane distance
    /// @return An orthographic projection matrix compatible with Vulkan's coordinate system
    static Mat4 FromOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

    /// @brief Creates a centered orthographic projection matrix suitable for Vulkan rendering
    /// @details Convenience method that creates an orthographic projection with a symmetric view volume
    ///          centered around the origin, specified by width and height.
    /// @param width The total width of the view volume
    /// @param height The total height of the view volume
    /// @param nearPlane The near clipping plane distance
    /// @param farPlane The far clipping plane distance
    /// @return A centered orthographic projection matrix compatible with Vulkan's coordinate system
    inline static Mat4 FromOrthographic(float width, float height, float nearPlane, float farPlane)
    {
        return FromOrthographic(-width/2, width/2, -height/2, height/2, nearPlane, farPlane);
    }

    /// @brief Overloads the multiplication assignment operator to multiply this matrix by another matrix.
    /// @details This method performs standard matrix multiplication and assigns the result to this matrix.
    /// @param[in] other The matrix to multiply with this matrix.
    /// @returns A reference to this matrix after the multiplication.
    Mat4& operator*=(const Mat4& other);

    /// @brief Modifies this matrix by applying a translation and returns a reference to this matrix.
    /// @details Applies the displacement to this matrix, allowing for method chaining.
    /// @param displacement The vector representing how far to move in each direction.
    /// @return A reference to this matrix after applying the translation.
    Mat4& Translate(const Vec3& displacement);

    /// @brief Modifies this matrix by applying scaling and returns a reference to this matrix.
    /// @details Applies the scale factors to this matrix, allowing for method chaining.
    /// @param scale The scale factors for x, y, and z axes.
    /// @return A reference to this matrix after applying the scaling.
    Mat4& Scale(const Vec3& scale);

    /// @brief Modifies this matrix by applying rotation around an axis and returns a reference to this matrix.
    /// @details Rotates this matrix around the specified axis by the given angle in radians, 
    ///          allowing for method chaining.
    /// @param angle The rotation angle in radians.
    /// @param axis The axis to rotate around (should be normalized).
    /// @return A reference to this matrix after applying the rotation.
    Mat4& Rotate(const float angle, const Vec3& axis);

    /// @brief Modifies this matrix by applying rotation around an axis and returns a reference to this matrix.
    /// @details Rotates this matrix around the specified axis by the given angle in degrees, 
    ///          allowing for method chaining. Internally converts degrees to radians.
    /// @param angleDeg The rotation angle in degrees.
    /// @param axis The axis to rotate around (should be normalized).
    /// @return A reference to this matrix after applying the rotation.
    Mat4& RotateDeg(const float angleDeg, const Vec3& axis);

    /// @brief Modifies this matrix by applying Euler angle rotation and returns a reference to this matrix.
    /// @details Applies rotation based on Euler angles in radians (pitch, yaw, roll),
    ///          allowing for method chaining. Uses quaternion conversion internally for better accuracy.
    /// @param eulerAngles The Euler angles in radians (x=pitch, y=yaw, z=roll).
    /// @return A reference to this matrix after applying the rotation.
    Mat4& Rotate(const Vec3& eulerAngles);

    /// @brief Modifies this matrix by applying Euler angle rotation and returns a reference to this matrix.
    /// @details Applies rotation based on Euler angles in degrees (pitch, yaw, roll),
    ///          allowing for method chaining. Internally converts degrees to radians and
    ///          uses quaternion conversion for better accuracy.
    /// @param eulerAnglesDeg The Euler angles in degrees (x=pitch, y=yaw, z=roll).
    /// @return A reference to this matrix after applying the rotation.
    Mat4& RotateDeg(const Vec3& eulerAnglesDeg);

    /// @brief Modifies this matrix by applying quaternion rotation and returns a reference to this matrix.
    /// @details Applies the rotation represented by the quaternion to this matrix,
    ///          allowing for method chaining. Using quaternions helps avoid gimbal lock issues.
    /// @param quat The quaternion representing the rotation to apply.
    /// @return A reference to this matrix after applying the rotation.
    Mat4& Rotate(const Quat& quat);

    /// @brief Inverses this matrix and returns a reference to the modified matrix.
    /// @details Replaces this matrix with its inverse, allowing for method chaining.
    ///          Useful for converting between coordinate spaces or creating view matrices.
    /// @returns A reference to this matrix after computing its inverse.
    /// @note This operation may fail if the matrix is singular (determinant is zero).
    inline Mat4& Mat4::Inverse()
    {
        return *this = WithInverse();
    }

    /// @brief Transposes this matrix and returns a reference to the modified matrix.
    /// @details Swaps rows and columns of this matrix in-place, allowing for method chaining.
    ///          Used in certain graphics operations such as normal transformation.
    /// @returns A reference to this matrix after computing its transpose.
    inline Mat4& Mat4::Transpose()
    {
        return *this = WithTranspose();
    }

    /// @brief Creates a new matrix by applying a translation to this matrix.
    /// @details Returns a new matrix without modifying the original.
    /// @param displacement The vector representing how far to move in each direction.
    /// @return A new matrix representing this matrix with the translation applied.
    Mat4 WithTranslation(const Vec3& displacement) const;

    /// @brief Applies scaling to this matrix and returns a new matrix.
    /// @details Creates a new matrix that represents the result of applying the scaling
    ///          to this matrix. This operation does not modify the original matrix.
    /// @param scale The scale factors for x, y, and z axes.
    /// @return A new matrix representing this matrix with the scaling applied.
    Mat4 WithScale(const Vec3& scale) const;

    /// @brief Applies rotation to this matrix and returns a new matrix.
    /// @details Creates a new matrix that represents the result of rotating this matrix
    ///          around the specified axis by the given angle. This operation does not
    ///          modify the original matrix.
    /// @param angle The rotation angle in radians.
    /// @param axis The axis to rotate around (should be normalized).
    /// @return A new matrix representing this matrix with the rotation applied.
    Mat4 WithRotation(const float angle, const Vec3& axis) const;

    /// @brief Applies rotation in degrees to this matrix and returns a new matrix.
    /// @details Convenience method that converts degrees to radians and applies rotation.
    ///          This operation does not modify the original matrix.
    /// @param angleDeg The rotation angle in degrees.
    /// @param axis The axis to rotate around (should be normalized).
    /// @return A new matrix representing this matrix with the rotation applied.
    inline Mat4 WithRotationDeg(const float angleDeg, const Vec3& axis) const
    {
        return WithRotation(angleDeg * DEG_TO_RAD, axis);
    }

    /// @brief Creates a new matrix by applying Euler angle rotation to this matrix.
    /// @details Returns a new matrix without modifying the original.
    /// @param eulerAngles The Euler angles in radians (pitch, yaw, roll).
    /// @return A new matrix representing this matrix with the rotation applied.
    Mat4 WithRotation(const Vec3& eulerAngles) const;

    /// @brief Creates a new matrix by applying Euler angle rotation in degrees to this matrix.
    /// @details Returns a new matrix without modifying the original.
    /// @param eulerAnglesDeg The Euler angles in degrees (pitch, yaw, roll).
    /// @return A new matrix representing this matrix with the rotation applied.
    Mat4 WithRotationDeg(const Vec3& eulerAnglesDeg) const;

    /// @brief Applies quaternion rotation to this matrix and returns a new matrix.
    /// @details Creates a new matrix that represents the result of applying the quaternion
    ///          rotation to this matrix. This operation does not modify the original matrix.
    /// @param rotation The quaternion representing the rotation to apply.
    /// @return A new matrix representing this matrix with the rotation applied.
    Mat4 WithRotation(const Quat& rotation) const;

    /// @brief Creates a new matrix that is the inverse of this matrix.
    /// @details Returns a new matrix without modifying the original.
    ///          The inverse of a matrix M is another matrix M' such that M * M' = M' * M = Identity.
    /// @returns A new matrix representing the inverse of this matrix.
    /// @throws May throw an exception if the matrix is singular (determinant is zero).
    Mat4 WithInverse() const;

    /// @brief Creates a new matrix that is the transpose of this matrix.
    /// @details Returns a new matrix without modifying the original.
    ///          The transpose of a matrix swaps its rows and columns.
    /// @returns A new matrix representing the transpose of this matrix.
    Mat4 WithTranspose() const;

    /// @brief Performs component-wise multiplication of two matrices.
    /// @details Multiplies each component of lhs with the corresponding component of rhs.
    /// @param lhs The first matrix.
    /// @param rhs The second matrix.
    /// @returns A new matrix with each component being the product of the corresponding components.
    static Mat4 Hadamard(const Mat4& lhs, const Mat4& rhs);

    /// @brief Gets the X basis vector (first column) of the matrix.
    /// @details Returns the x-axis basis vector which represents the 
    ///          right direction in the matrix's transformation.
    /// @returns A Vec4 containing the first column of the matrix.
    inline Vec4 XBasis() const
    {
        return Vec4{ internal_mat[0][0], internal_mat[0][1], internal_mat[0][2], internal_mat[0][3] };
    }

    /// @brief Gets the Y basis vector (second column) of the matrix.
    /// @details Returns the y-axis basis vector which represents the 
    ///          up direction in the matrix's transformation.
    /// @returns A Vec4 containing the second column of the matrix.
    inline Vec4 YBasis() const
    {
        return Vec4{ internal_mat[1][0], internal_mat[1][1], internal_mat[1][2], internal_mat[1][3] };
    }

    /// @brief Gets the Z basis vector (third column) of the matrix.
    /// @details Returns the z-axis basis vector which represents the 
    ///          forward direction in the matrix's transformation.
    /// @returns A Vec4 containing the third column of the matrix.
    inline Vec4 ZBasis() const
    {
        return Vec4{ internal_mat[2][0], internal_mat[2][1], internal_mat[2][2], internal_mat[2][3] };
    }

    /// @brief Gets the translation vector (fourth column) of the matrix.
    /// @details Returns the translation component of the transformation matrix,
    ///          representing the position in world space.
    /// @returns A Vec4 containing the fourth column of the matrix.
    inline Vec4 Translation() const
    {
        return Vec4{ internal_mat[3][0], internal_mat[3][1], internal_mat[3][2], internal_mat[3][3] };
    }

    /// @brief Alias for Translation(). Gets the position vector from the matrix.
    /// @returns A Vec4 containing the translation/position component.
    inline Vec4 Position() const { return Translation(); }

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

/// @brief Overloads the multiplication operator to multiply a matrix by a vector.
/// @details Performs standard matrix-vector multiplication.
/// @param[in] lhs The matrix operand.
/// @param[in] rhs The vector operand.
/// @returns A new vector representing the transformation of the vector by the matrix.
inline Vec4 operator*(const Mat4& lhs, const Vec4& rhs)
{
    return Vec4(lhs.internal_mat * static_cast<glm::vec4>(rhs));
}

} // namespace velecs::math
