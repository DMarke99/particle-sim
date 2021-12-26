#pragma once
#include "math.hpp"
#include <iostream>

class Vec3d {
    public:
        float x, y, z;
};

Vec3d operator+(const Vec3d& vec1, const Vec3d& vec2);
Vec3d operator-(const Vec3d& vec1, const Vec3d& vec2);
Vec3d operator*(const float& k, const Vec3d& vec);
Vec3d operator*(const Vec3d& vec, const float& k);
Vec3d operator/(const Vec3d& vec, const float& k);

void operator+=(Vec3d& vec1, const Vec3d& vec2);
void operator-=(Vec3d& vec1, const Vec3d& vec2);
void operator*=(Vec3d& vec, const float& k);
void operator/=(Vec3d& vec, const float& k);

float sumsq(const Vec3d& vec);
Vec3d normed(const Vec3d& vec);
std::ostream &operator<<(std::ostream &os, const Vec3d& vec);