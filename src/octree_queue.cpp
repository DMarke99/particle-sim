#include "octree_queue.hpp"

OctreeQueue::OctreeQueue(
    const Vec3d& center, 
    const float& width
): particles({}), quadrants({}), center(center), width(width), depth(0), parent(nullptr), root(this) {
    this->children = { nullptr };
};

OctreeQueue::OctreeQueue(
    const Vec3d& center, 
    const float& width,
    const int& depth,
    OctreeQueue* parent, 
    OctreeQueue* root
): particles({}), quadrants({}), center(center), width(width), depth(depth), parent(parent), root(root) {
    this->children = { nullptr };
};


void OctreeQueue::add_particle(const Particle& particle) {
    if (this->particles.size() == 1) {
        this->add_particle_to_children(this->particles.front());
    }

    this->particles.push_back(particle);
    this->quadrants.push_back(this->quadrant(particle));
    this->weighted_pos += (particle.mass * particle.pos);
    this->mass += particle.mass;

    if (this->particles.size() > 0) {
        this->add_particle_to_children(particle);
    }


};

void OctreeQueue::add_particle_to_children(const Particle& particle) {
    int idx = this->quadrants.back();
    if (this->depth < MAX_OCTREE_DEPTH) {
        if (this->children[idx] == nullptr) {
            this->children[idx] = std::make_unique<OctreeQueue>(
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


void OctreeQueue::pop_particle() {
    if (this->particles.size() > 1) {
        this->pop_particle_from_children();
    }
    Particle particle = this->particles.front();
    this->particles.pop_front();
    this->quadrants.pop_front();
    this->weighted_pos -= (particle.mass * particle.pos);
    this->mass -= particle.mass;

    if (this->particles.size() == 1) {
        this->pop_particle_from_children();
    }
};

void OctreeQueue::pop_particle_from_children() {
    int idx = this->quadrants.front();
    if (this->children[idx] != nullptr) {
        this->children[idx]->pop_particle();
        if (this->children[idx]->size() == 0) {
            this->children[idx] = nullptr;
        }
    }
};


void OctreeQueue::remove_particle(const Particle& particle) {
    int idx = this->index(particle);
    if (idx >= 0) {
        this->particles.erase (this->particles.begin()+idx);
        this->weighted_pos -= (particle.mass * particle.pos);
        this->mass -= particle.mass;
        this->remove_particle_from_children(particle);
    }

    if (this->particles.size() == 1) {
        this->remove_particle_from_children(this->particles[0]);
    }
};

void OctreeQueue::remove_particle_from_children(const Particle& particle) {
    //std::cout << particle.pos << std::endl;
    //std::cout << this->width << std::endl;
    //std::cout << this->center << std::endl;
    int idx = this->quadrant(particle);
    if (idx >= 0) {
        //std::cout << idx << std::endl;
        if (this->children[idx] != nullptr) {
            this->children[idx]->remove_particle(particle);
            if (this->children[idx]->size() == 0) {
                this->children[idx] = nullptr;
            }
        }
    }
};


Vec3d OctreeQueue::center_of_mass() {
    return this->particles.size() == 0 ? weighted_pos : (weighted_pos / mass);
};

bool OctreeQueue::contains(const Particle& particle) {
    for (auto _p : this->particles){
        if (_p.get().ID == particle.ID) return true;
    }
    return false;
};

int OctreeQueue::index(const Particle& particle) {
    int idx = 0;
    for (auto _p : this->particles){
        if (_p.get().ID == particle.ID) return idx;
        ++idx;
    }
    return -1;
};

bool OctreeQueue::is_in_range(const Particle& particle) {
    Vec3d relative_pos = particle.pos - this->center;
    if (relative_pos.x > this->width/2) return false;
    else if (relative_pos.x < -this->width/2) return false;
    else if (relative_pos.y > this->width/2) return false;
    else if (relative_pos.y < -this->width/2) return false;
    else if (relative_pos.z > this->width/2) return false;
    else if (relative_pos.z < -this->width/2) return false;
    else return true;
};

int OctreeQueue::quadrant(const Particle& particle) {
    //if (!this->is_in_range(particle)) return -1;

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

Vec3d OctreeQueue::get_force(const Particle& particle, const float& approx_threshold) {

    if (this->particles.size() == 0 or this->mass == 0) {
        return {0,0,0};

    } else if (this->particles.size() == 1) {
        return grav_force(
            particle.mass, 
            this->mass, 
            particle.pos, 
            this->center_of_mass()
        );
    } else {
        float factor = sumsq(this->center_of_mass() - particle.pos) / (this->width * this->width);
        float threshold = approx_threshold * approx_threshold;

        if (factor >= threshold) {
            Vec3d total_force = {0,0,0};
            bool is_leaf = true;
            for (auto& child : this->children){
                if (child != nullptr) {
                    total_force += child->get_force(particle, approx_threshold);
                    is_leaf = false;
                }
            }
            if (!is_leaf) {
                return total_force;
            }
        }

        return grav_force(
            particle.mass, 
            this->mass, 
            particle.pos, 
            this->center_of_mass()
        );

    }
}