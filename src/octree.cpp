#include "octree.hpp"

Octree::Octree(
    const Vec3d& center, 
    const float& width
): particles({}), center(center), width(width), depth(0), parent(nullptr), root(this) {
    this->children.fill(nullptr);
};

Octree::Octree(
    const Vec3d& center, 
    const float& width,
    const int& depth,
    Octree* parent, 
    Octree* root
): particles({}), center(center), width(width), depth(depth), parent(parent), root(root) {
    this->children.fill(nullptr);
};


void Octree::add_particle(Particle& particle) {
    if (this->particles.size() == 1) {
        this->add_particle_to_children(*this->particles[0]);
    }

    Particle* ref = &particle;
    this->particles.push_back(ref);
    this->weighted_pos += (particle.mass * particle.pos);
    this->mass += particle.mass;

    if (this->particles.size() > 1) {
        this->add_particle_to_children(particle);
    }
};

void Octree::remove_particle(Particle& particle) {
    int idx = this->index(particle);
    if (idx >= 0) {
        this->particles.erase (this->particles.begin()+idx);
        this->weighted_pos -= (particle.mass * particle.pos);
        this->mass -= particle.mass;
        this->remove_particle_from_children(particle);
    }

    if (this->particles.size() == 1) {
        this->remove_particle_from_children(*this->particles[0]);
    }
};

void Octree::add_particle_to_children(Particle& particle) {
    int idx = this->quadrant(particle);
    if (idx >= 0 and this->depth < MAX_OCTREE_DEPTH) {
        if (this->children[idx] == nullptr) {
            this->children[idx] = new Octree(
                this->center+quadrant_idx_to_vec(idx)*this->width, 
                this->width/2,
                this->depth+1, 
                this, 
                this->root
            );
        }
        this->children[idx]->add_particle(particle);
    } 
};

void Octree::remove_particle_from_children(Particle& particle) {
    //std::cout << particle.pos << std::endl;
    //std::cout << this->width << std::endl;
    //std::cout << this->center << std::endl;
    int idx = this->quadrant(particle);
    //std::cout << idx << std::endl;
    if (this->children[idx] != nullptr) {
        this->children[idx]->remove_particle(particle);
        if (this->children[idx]->get_particles().size() == 0) {
            delete this->children[idx];
            this->children[idx] = nullptr;
        }
    }
};

Vec3d Octree::center_of_mass() {
    return this->particles.size() == 0 ? weighted_pos : (weighted_pos / mass);
};

bool Octree::contains(const Particle& particle) {
    for (auto _p : this->particles){
        if (_p == &particle) return true;
    }
    return false;
};

int Octree::index(const Particle& particle) {
    int idx = 0;
    for (auto _p : this->particles){
        if (_p == &particle) return idx;
        ++idx;
    }
    return -1;
};

bool Octree::is_in_range(const Particle& particle) {
    Vec3d relative_pos = particle.pos - this->center;
    if (relative_pos.x > this->width/2) return false;
    else if (relative_pos.x < -this->width/2) return false;
    else if (relative_pos.y > this->width/2) return false;
    else if (relative_pos.y < -this->width/2) return false;
    else if (relative_pos.z > this->width/2) return false;
    else if (relative_pos.z < -this->width/2) return false;
    else return true;
};

int Octree::quadrant(const Particle& particle) {
    if (!this->is_in_range(particle)) return -1;

    int idx = 0;
    if (particle.pos.x > this->center.x) idx += 1;
    if (particle.pos.y > this->center.y) idx += 2;
    if (particle.pos.z > this->center.z) idx += 4;
    return idx;

};

Vec3d quadrant_idx_to_vec(const int& idx) {
    switch (idx) {
        case 0: return {-0.25, -0.25, -0.25};
        case 1: return {0.25, -0.25, -0.25};
        case 2: return {-0.25, 0.25, -0.25};
        case 3: return {0.25, 0.25, -0.25};
        case 4: return {-0.25, -0.25, 0.25};
        case 5: return {0.25, -0.25, 0.25};
        case 6: return {-0.25, 0.25, 0.25};
        case 7: return {0.25, 0.25, 0.25};
        default: throw std::invalid_argument("received invalid index");
    }
}

Vec3d Octree::get_force(const Particle& particle, const float& approx_threshold) {

    if (this->particles.size() == 0) {
        return {0,0,0};

    } else if (this->particles.size() == 1) {
        if (this->contains(particle)) {
            return {0,0,0};
        } else {
            return grav_force(
                particle.mass, 
                this->particles[0]->mass, 
                particle.pos, 
                this->particles[0]->pos
            );
        }
    } else {
        float factor = sumsq(this->center_of_mass() - particle.pos) / (this->width * this->width);
        float threshold = approx_threshold * approx_threshold;

        if (factor > threshold or this->is_in_range(particle)) {
            Vec3d total_force = {0,0,0};
            bool is_leaf = true;
            for (auto child : this->children){
                if (child != nullptr) {
                    total_force += child->get_force(particle, approx_threshold);
                    is_leaf = false;
                }
            }
            if (!is_leaf) return total_force;
        }
        return grav_force(
            particle.mass, 
            this->mass, 
            particle.pos, 
            this->center_of_mass()
        );

    }
}