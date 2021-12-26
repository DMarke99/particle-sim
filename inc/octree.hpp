#include <vector>
#include "physics.hpp"

const int MAX_DEPTH = 32;

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

        std::vector<Octree>* children = nullptr;

    public:
        Octree(const Vec3d& center, const float& width);
        Octree(
            const Vec3d& center, 
            const float& width,
            const int& depth, 
            Octree* parent, 
            Octree* root
        );

        void create_children();
        void remove_children();

        void add_particle(Particle& particle);
        void remove_particle(Particle& particle);
        void add_particle_to_children(Particle& particle);
        void remove_particle_from_children(Particle& particle);

        Vec3d center_of_mass();

        bool contains(Particle& particle);
        int index(Particle& particle);
        bool is_in_range(const Particle& particle);
        int quadrant(const Particle& particle);
};

Vec3d quadrant_idx_to_vec(const int& idx);