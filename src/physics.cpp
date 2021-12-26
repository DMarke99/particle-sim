#include "physics.hpp"

Vec3d grav_force(const Particle& p1, const Particle& p2) {
    Vec3d dir = p1.pos - p2.pos;
    return GRAV_CONST * p1.mass * p2.mass / sumsq(dir) * normed(dir);
}