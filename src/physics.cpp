#include "physics.hpp"
std::default_random_engine gen;

int Particle::ID_ctr = 0;

Particle::Particle(
    const float& mass, 
    const Vec3d& pos,
    const Vec3d& v,
    const Vec3d& a
): mass(mass), pos(pos), v(v), a(a), ID(ID_ctr++) {}

Vec3d grav_force(
    const float& mass1, 
    const float& mass2, 
    const Vec3d& pos1, 
    const Vec3d& pos2
) {
    // convention is the force that pos2 applies on pos1
    Vec3d dir = pos2 - pos1;

    float magnitude = GRAV_CONST * mass1 * mass2 / (GRAV_EPSILON + sumsq(dir));
    return magnitude * normed(dir);
}

Particle generate_random_particle(
    const float& mass, 
    const Vec3d& center, 
    const float& width, 
    const float& avg_speed
) {

    std::uniform_real_distribution<float> coord_loc(-0.5,0.5);
    Vec3d relative_pos = {coord_loc(gen), coord_loc(gen), coord_loc(gen)};
    Vec3d pos = center + width * relative_pos;

    std::normal_distribution<float> vec_component(0, avg_speed * fast_inv_sqrt(3));
    Vec3d v = {vec_component(gen), vec_component(gen), vec_component(gen)};

    return {mass, pos, v, {0,0,0}};
}