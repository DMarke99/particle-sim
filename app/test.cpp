#include <iostream>
#include "simulation.hpp"
#include <math.h>
#include <ctime>
#include <ratio>
#include <chrono>

void test_math(){
    std::cout << "Test Math" << std::endl;

    Mat3d M = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Vec3d v = {1,2,3};

    std::cout << M << std::endl;
    std::cout << (M * v) << std::endl;
    std::cout << std::endl;
}


void simple_octree(){
    std::cout << "Small Example" << std::endl;

    Particle p1 = {1, {1, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    Particle p2 = {1, {1, 1, 0}, {0, 0, 0}, {0, 0, 0} };
    OctreeQueue octree = OctreeQueue({0, 0, 0}, 4);

    octree.add_particle(p1);
    octree.add_particle(p2);

    std::cout << "Is Particle 1 in tree?: " << octree.contains(p1) << std::endl;
    std::cout << "Is Particle 2 in tree?: " << octree.contains(p2) << std::endl;
    std::cout << std::endl;
}


void check_octree(){

    std::cout << "Large Example" << std::endl;
    Particle p1 = {1, {1, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    Particle p2 = {1, {1, 1, 0}, {0, 0, 0}, {0, 0, 0} };
    Particle p3 = {1, {1, 1, 0.5}, {0, 0, 0}, {0, 0, 0} };
    Particle p4 = {1, {1, 1, 0.5}, {0, 0, 0}, {0, 0, 0} };
    Particle p5 = {1, {1, 1, 1}, {0, 0, 0}, {0, 0, 0} };
    Particle p6 = {1, {1, 1, 0.55}, {0, 0, 0}, {0, 0, 0} };
    OctreeQueue octree = OctreeQueue({0, 0, 0}, 4);

    octree.add_particle(p1);
    octree.add_particle(p2);
    octree.add_particle(p3);
    octree.add_particle(p4);
    octree.remove_particle(p3);
    octree.add_particle(p6);

    std::cout << "Is Particle 1 in tree?: " << octree.contains(p1) << std::endl;
    std::cout << "Is Particle 2 in tree?: " << octree.contains(p2) << std::endl;
    std::cout << "Is Particle 3 in tree?: " << octree.contains(p3) << std::endl;
    std::cout << "Is Particle 4 in tree?: " << octree.contains(p4) << std::endl;
    std::cout << "Is Particle 5 in tree?: " << octree.contains(p5) << std::endl;
    std::cout << "Is Particle 6 in tree?: " << octree.contains(p6) << std::endl;

    Vec3d com = octree.center_of_mass();

    std::cout << "Center of mass: " << com << std::endl;
    std::cout << std::endl;

    std::cout << "Test Forces" << std::endl;
    std::cout << octree.get_force(p3, 0.0) << std::endl;
    
}

void run_sim(){

    int N = 2500;
    int n_iters = 100;
    ParticleSimulator sim = ParticleSimulator(N);
    using namespace std::chrono;

    std::cout << "Simulating " << N << " particles" << std::endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i = 0; i < n_iters; ++i) {
        sim.step();
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "Finished in " << time_span.count() << " seconds." << std::endl;
    std::cout << "Implied FPS: " << floor(100/time_span.count()) << std::endl;
}


int main() {
    test_math();
    simple_octree();
    check_octree();
    return 0;
}