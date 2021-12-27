#pragma once
#include "octree.hpp"
#include <math.h>

class ParticleSimulator {
    public:
        std::vector<Particle> particles = {};
        Vec3d center;
        float width;
        Octree octree;
        ParticleSimulator(
            const int& N, 
            const Vec3d& center={0,0,0}, 
            const float& width=1
        );
        void update_forces(const float& approx_threshold);
        void move_particles(const float& dt); 
        void update_octree(); 
        void step(const float& dt=0.05, const float& approx_threshold=1.0);  
};

float reflect_pos_coord(const float& x, const float& width);
float reflect_velocity_coord(const float& v, const float& x, const float& width);