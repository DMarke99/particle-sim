#pragma once
#include "vec3d.hpp"

const float GRAV_CONST = 1;

class Particle {
    public:
        float mass;
        Vec3d pos;
        Vec3d v;
        Vec3d a;
};

Vec3d grav_force(const Particle& p1, const Particle& p2);