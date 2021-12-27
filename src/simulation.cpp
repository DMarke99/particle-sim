#include "simulation.hpp"

ParticleSimulator::ParticleSimulator(
    const int& N, 
    const Vec3d& center, 
    const float& width
): center(center), width(width), octree(center, width) {
    for (int i = 0; i < N; ++i) {
        Particle particle = generate_random_particle(1, this->center, this->width, 2);
        this->particles.push_back(particle);
        this->octree.add_particle(particle);
    };
};

void ParticleSimulator::update_forces(const float& approx_threshold) {
    for (auto particle : this->particles) {
        particle.a = this->octree.get_force(particle, approx_threshold) / particle.mass;
        //std::cout << particle.a << std::endl;
    }
};

void ParticleSimulator::move_particles(const float& dt) {
    for (auto particle : this->particles) {

        // updates position and velocity
        particle.pos += 0.5 * particle.v * dt;
        particle.v += particle.a * dt - 0.1 * particle.v * dt;
        particle.pos += 0.5 * particle.v * dt;

        // reflects positions at boundary
        particle.v.x = reflect_velocity_coord(particle.v.x, particle.pos.x, this->width);
        particle.v.y = reflect_velocity_coord(particle.v.y, particle.pos.y, this->width);
        particle.v.z = reflect_velocity_coord(particle.v.z, particle.pos.z, this->width);

        particle.pos.x = reflect_pos_coord(particle.pos.x, this->width);
        particle.pos.y = reflect_pos_coord(particle.pos.y, this->width);
        particle.pos.z = reflect_pos_coord(particle.pos.z, this->width);

    }

};

void ParticleSimulator::update_octree() {
    this->octree = Octree(this->center, this->width);
    for (auto particle : this->particles) {
        this->octree.add_particle(particle);
    }
};

void ParticleSimulator::step(const float& dt, const float& approx_threshold) {
    this->update_forces(approx_threshold);
    this->move_particles(dt);
    this->update_octree();
};

float reflect_pos_coord(const float& x, const float& width){
    float x_n = 0.5 * x / width - 0.25;
    return 2 * width * abs(x_n - floor(x_n) - 0.5);
}

float reflect_velocity_coord(const float& v, const float& x, const float& width){
    float x_n = 0.5 * x / width - 0.25;
    float factor = sgn(x_n - floor(x_n) - 0.5);
    return v * factor;
}