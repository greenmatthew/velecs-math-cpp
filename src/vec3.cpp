#include "vec3.hpp"

Vec3 Vec3::add(const Vec3& other) const
{
    return {x + other.x, y + other.y, z + other.z};
}