#include <iostream>
#include <iomanip>

#include "vec2.hpp"
#include "vec3.hpp"

#include <glm/common.hpp>
#include <glm/mat4x4.hpp>

std::ostream& operator<<(std::ostream& os, const glm::mat4& mat)
{
    for (int row = 0; row < 4; ++row) {
        os << "| ";
        for (int col = 0; col < 4; ++col) {
            std::cout << std::setw(10) << std::setprecision(4) << mat[col][row] << " ";
        }
        os << "|" << std::endl;
    }
    return os;
}

int main()
{
    Vec2 v2 = Vec2{1, 1};
    v2 = v2.add(v2);
    std::cout << '(' << v2.x << ',' << v2.y << ')' << std::endl;

    Vec3 v3 = Vec3{1, 1, 1};
    v3 = v3.add(v3);
    std::cout << '(' << v3.x << ',' << v3.y << ',' << v3.z << ')' << std::endl;

    glm::mat4 identity_mat = glm::mat4(1.0f);
    std::cout << identity_mat << std::endl;

    return EXIT_SUCCESS;
}