#pragma once
#include <vector>
#include "physics.hpp"
#include <array>
#include <stdexcept>

const int MAX_OCTREE_DEPTH = 16;

class Octree {
    private:
        std::vector<Particle*> particles;
        Vec3d center;
        float width;
        int depth;

        Octree* parent;
        Octree* root;

        float mass = 0;
        Vec3d weighted_pos = {0, 0, 0};

        std::array<Octree*, 8> children;

    public: 
        Octree(const Vec3d& center, const float& width);
        Octree(
            const Vec3d& center, 
            const float& width,
            const int& depth, 
            Octree* parent, 
            Octree* root
        );

        std::vector<Particle*> get_particles() { return this->particles; };
        std::array<Octree*, 8> get_children() { return this->children; };

        void add_particle(Particle& particle);
        void remove_particle(Particle& particle);
        void add_particle_to_children(Particle& particle);
        void remove_particle_from_children(Particle& particle);

        Vec3d center_of_mass();

        bool contains(const Particle& particle);
        int index(const Particle& particle);
        bool is_in_range(const Particle& particle);
        int quadrant(const Particle& particle);

        Vec3d get_force(const Particle& particle, const float& shrinkage);
};

Vec3d quadrant_idx_to_vec(const int& idx);
