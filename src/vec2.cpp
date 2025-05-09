#include "vec2.hpp"

Vec2 Vec2::add(const Vec2& other) const
{
    return {x + other.x, y + other.y};
}