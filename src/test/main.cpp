#include <iostream>
#include <iomanip>

#include "velecs/math/Vec2.hpp"
#include "velecs/math/Vec3.hpp"
#include "velecs/math/Vec4.hpp"
#include "velecs/math/Quat.hpp"
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

    std::cout << Mat4::FromPosition(Vec3::FORWARD * 5.0f) << std::endl;

    Mat4 compTransforms = Mat4::IDENTITY
        .WithScale(Vec3(1, 2, 3))
        .WithRotation(45.0f * DEG_TO_RAD, Vec3::DOWN)
        .WithTranslation((Vec3::FORWARD * 25) + (Vec3::RIGHT * 5))
        ;
    std::cout << compTransforms << std::endl;

    compTransforms = Mat4::IDENTITY;
    Mat4 S = Mat4::FromScale(Vec3(1, 2, 3));
    Mat4 R = Mat4::FromRotationDeg(45.0f * Vec3::UP);
    Mat4 T = Mat4::FromPosition((Vec3::FORWARD * 25) + (Vec3::RIGHT * 5));

    compTransforms = compTransforms * S;
    std::cout << "1.\n" << compTransforms << std::endl;
    compTransforms = compTransforms * R;
    std::cout << "2.\n" << compTransforms << std::endl;
    compTransforms = compTransforms * T;
    std::cout << "3.\n" << compTransforms << std::endl;


    Vec4 triV1 = Vec4::CreatePoint(-0.5, -0.5,  0.0);
    Vec4 triV2 = Vec4::CreatePoint( 0.5, -0.5,  0.0);
    Vec4 triV3 = Vec4::CreatePoint( 0.0,  0.5,  0.0);

    Vec3 triPos = Vec3::FORWARD * 10;
    Vec3 triRot = 180.0f * Vec3::UP;
    Vec3 triScale = Vec3::ONE;
    Mat4 triPosMat = Mat4::FromPosition(triPos);
    Mat4 triRotMat = Mat4::FromRotationDeg(triRot);
    Mat4 triScaleMat = Mat4::FromScale(triScale);

    Mat4 triModelMat = triScaleMat * triRotMat * triPosMat;
    std::cout << "triangle Model Matrix:\n" << triModelMat << std::endl;

    // std::cout << "triangle vertex 1 world space coord:\n" << triModelMat * triV1 << std::endl;
    // std::cout << "triangle vertex 2 world space coord:\n" << triModelMat * triV2 << std::endl;
    // std::cout << "triangle vertex 3 world space coord:\n" << triModelMat * triV3 << std::endl;

    return EXIT_SUCCESS;
}