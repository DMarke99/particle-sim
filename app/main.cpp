#include <iostream>
#include "vec3d.hpp"
#include "physics.hpp"
#include "octree.hpp"

void say_hello(){

    Particle p1 = {1, {1, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    Particle p2 = {1, {1, 1, 0}, {0, 0, 0}, {0, 0, 0} };
    Particle p3 = {1, {1, 1, 0.05}, {0, 0, 0}, {0, 0, 0} };
    Particle p4 = {1, {1, 1, 1}, {0, 0, 0}, {0, 0, 0} };

    Octree octree = Octree({0, 0, 0}, 4);

    octree.add_particle(p1);
    octree.add_particle(p2);
    octree.add_particle(p3);

    std::cout << "Is Particle 1 in tree?: " << octree.contains(p1) << std::endl;
    std::cout << "Is Particle 2 in tree?: " << octree.contains(p2) << std::endl;
    std::cout << "Is Particle 3 in tree?: " << octree.contains(p3) << std::endl;
    std::cout << "Is Particle 4 in tree?: " << octree.contains(p4) << std::endl;

    Vec3d com = octree.center_of_mass();

    std::cout << "Center of mass: " << com << std::endl;

}

int main() {
    say_hello();
    return 0;
}