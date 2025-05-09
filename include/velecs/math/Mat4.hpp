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

#include <glm/mat4x4.hpp>

namespace velecs::math {

/// @class Mat4
/// @brief Brief description.
///
/// Rest of description.
class Mat4 {
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

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::math
