#pragma once
#include <vector>
#include "physics.hpp"
#include <array>
#include <stdexcept>

const int MAX_OCTREE_DEPTH = 16;

class OctreeQueue {
    private:
        std::vector<std::reference_wrapper<const Particle>> particles;
        Vec3d center;
        float width;
        int depth;

        OctreeQueue* parent;
        OctreeQueue* root;

        float mass = 0;
        Vec3d weighted_pos = {0, 0, 0};

        std::array<OctreeQueue*, 8> children;

    public: 
        OctreeQueue(const Vec3d& center, const float& width);
        OctreeQueue(
            const Vec3d& center, 
            const float& width,
            const int& depth, 
            OctreeQueue* parent, 
            OctreeQueue* root
        );

        size_t size() { return this->particles.size(); };
        std::vector<std::reference_wrapper<const Particle>> get_particles() { return this->particles; };
        std::array<OctreeQueue*, 8> get_children() { return this->children; };

        void add_particle(const Particle& particle);
        void remove_particle(const Particle& particle);
        void add_particle_to_children(const Particle& particle);
        void remove_particle_from_children(const Particle& particle);

        Vec3d center_of_mass();

        bool contains(const Particle& particle);
        int index(const Particle& particle);
        bool is_in_range(const Particle& particle);
        int quadrant(const Particle& particle);

        Vec3d get_force(const Particle& particle, const float& approx_threshold);
};

Vec3d quadrant_idx_to_vec(const int& idx);
