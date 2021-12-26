#include "octree.hpp"

Octree::Octree(
    const Vec3d& center, 
    const float& width
): particles({}), center(center), width(width), depth(0), parent(nullptr), root(this) {};

Octree::Octree(
    const Vec3d& center, 
    const float& width,
    const int& depth,
    Octree* parent, 
    Octree* root
): particles({}), center(center), width(width), depth(depth), parent(parent), root(root) {};

void Octree::create_children(){
    if (this->children == nullptr) {
        this->children = new std::vector<Octree>();
        for (int i = 0; i < 8; ++i) {
            Vec3d new_center = this->center + quadrant_idx_to_vec(i) * this->width / 4;
            float new_width = this->width / 2;
            this->children->emplace_back(center, width, this->depth + 1, this, this->root);
        }
    }
}

void Octree::remove_children(){
    if (this->children != nullptr) {
        delete this->children;
        this->children = nullptr;
    }
}

void Octree::add_particle(Particle& particle) {
    if (this->particles.size() == 1 and this->children == nullptr) {
        this->create_children();

        for (auto p : this->particles){
            this->add_particle_to_children(*p);
        }
    }

    Particle* ref = &particle;
    this->particles.push_back(ref);
    this->weighted_pos += (particle.mass * particle.pos);
    this->mass += particle.mass;
    this->add_particle_to_children(particle);

};

void Octree::remove_particle(Particle& particle) {
    int idx = this->index(particle);
    if (idx >= 0) {
        this->particles.erase (this->particles.begin()+idx);
        this->weighted_pos -= (particle.mass * particle.pos);
        this->mass -= particle.mass;
        this->remove_particle_from_children(particle);
    }

    if (this->particles.size() == 0) {
        this->remove_children();
    }
};

void Octree::add_particle_to_children(Particle& particle) {
    if (this->children != nullptr) {
        int idx = this->quadrant(particle);
        (*(this->children))[idx].add_particle(particle);
    }
};

void Octree::remove_particle_from_children(Particle& particle) {
    if (this->children != nullptr) {
        int idx = this->quadrant(particle);
        (*(this->children))[idx].remove_particle(particle);
    }
};

Vec3d Octree::center_of_mass() {
    return this->particles.size() == 0 ? weighted_pos : (weighted_pos / mass);
};

bool Octree::contains(Particle& particle) {
    for (auto _p : this->particles){
        if (_p == &particle) return true;
    }
    return false;
};

int Octree::index(Particle& particle) {
    int idx = 0;
    for (auto _p : this->particles){
        if (_p == &particle) return idx;
        ++idx;
    }
    return -1;
};

bool Octree::is_in_range(const Particle& particle) {
    Vec3d relative_pos = particle.pos - this->center;
    if (relative_pos.x > this->width) return false;
    else if (relative_pos.x < -this->width) return false;
    else if (relative_pos.y > this->width) return false;
    else if (relative_pos.y < -this->width) return false;
    else if (relative_pos.z > this->width) return false;
    else if (relative_pos.z < -this->width) return false;
    else return true;
};

int Octree::quadrant(const Particle& particle) {
    if (!this->is_in_range(particle)) return -1;

    int idx = 0;
    if (particle.pos.x <= this->center.x) idx += 1;
    if (particle.pos.y <= this->center.y) idx += 2;
    if (particle.pos.z <= this->center.z) idx += 4;
    return idx;

};

Vec3d quadrant_idx_to_vec(const int& idx) {
    switch (idx) {
        case 0: return {-1, -1, -1};
        case 1: return {1, -1, -1};
        case 2: return {-1, 1, -1};
        case 3: return {1, 1, -1};
        case 4: return {-1, -1, 1};
        case 5: return {1, -1, 1};
        case 6: return {-1, 1, 1};
        case 7: return {1, 1, 1};
        default: return {0, 0, 0};
    }
}