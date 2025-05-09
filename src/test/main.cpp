#include <iostream>

#include "vec2.hpp"
#include "vec3.hpp"

int main()
{
    Vec2 v2 = Vec2{1, 1};
    v2 = v2.add(v2);
    std::cout << '(' << v2.x << ',' << v2.y << ')' << std::endl;

    Vec3 v3 = Vec3{1, 1, 1};
    v3 = v3.add(v3);
    std::cout << '(' << v3.x << ',' << v3.y << ',' << v3.z << ')' << std::endl;

    return EXIT_SUCCESS;
}