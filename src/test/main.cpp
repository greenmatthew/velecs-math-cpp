#include <iostream>
#include <iomanip>

#include "velecs/math/Vec2.hpp"
#include "velecs/math/Vec3.hpp"
#include "velecs/math/Mat4.hpp"

#include <glm/common.hpp>
#include <glm/mat4x4.hpp>

using namespace velecs::math;

int main()
{
    Vec2 v2 = Vec2{1, 1};
    v2 = v2 + v2;
    std::cout << v2 << std::endl;

    Vec3 v3 = Vec3{1, 1, 1};
    v3 = v3 + v3;
    std::cout << v3 << std::endl;

    Mat4 mat = Mat4(3.0f);
    std::cout << mat << std::endl;

    return EXIT_SUCCESS;
}