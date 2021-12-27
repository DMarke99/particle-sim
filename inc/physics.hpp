#pragma once
#include "vec3d.hpp"
#include <random>

const float GRAV_CONST = 1;

class Particle {
    public:
        float mass;
        Vec3d pos;
        Vec3d v;
        Vec3d a;
};

Vec3d grav_force(
    const float& mass1, 
    const float& mass2, 
    const Vec3d& pos1, 
    const Vec3d& pos2
);

Particle generate_random_particle(
    const float& mass, 
    const Vec3d& center, 
    const float& width, 
    const float& avg_speed
);