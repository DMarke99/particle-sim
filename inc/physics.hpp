#pragma once
#include "vec3d.hpp"
#include <random>

const float GRAV_CONST = 5e-6;
const float GRAV_EPSILON = 1e-3;
const float DRAG_COEFF = 0.5;

class Particle {
    private:
        static int ID_ctr;
    public:
        int ID;
        float mass;
        Vec3d pos;
        Vec3d v;
        Vec3d a;
        Particle(
            const float& mass, 
            const Vec3d& pos,
            const Vec3d& v,
            const Vec3d& a
        );
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
