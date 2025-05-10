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

    std::cout << Mat4::IDENTITY << std::endl;

    std::cout << Mat4::CreateTranslation(Vec3::FORWARD * 5.0f) << std::endl;

    Mat4 compTransforms = Mat4::IDENTITY
        .Scaled(Vec3(1, 2, 3))
        .Rotated(45.0f * DEG_TO_RAD, Vec3::DOWN)
        .Translated((Vec3::FORWARD * 25) + (Vec3::RIGHT * 5))
        ;
    std::cout << compTransforms << std::endl;

    compTransforms = Mat4::IDENTITY;
    Mat4 S = Mat4::CreateScale(Vec3(1, 2, 3));
    Mat4 R = Mat4::CreateRotation(45.0f * DEG_TO_RAD, Vec3::DOWN);
    Mat4 T = Mat4::CreateTranslation((Vec3::FORWARD * 25) + (Vec3::RIGHT * 5));

    compTransforms = compTransforms * S;
    std::cout << "1.\n" << compTransforms << std::endl;
    compTransforms = compTransforms * R;
    std::cout << "2.\n" << compTransforms << std::endl;
    compTransforms = compTransforms * T;
    std::cout << "3.\n" << compTransforms << std::endl;

    return EXIT_SUCCESS;
}