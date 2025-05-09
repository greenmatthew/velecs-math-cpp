#pragma once

class Vec3 {
public:
    float x, y, z;

public:
    Vec3 add(const Vec3& other) const;
};