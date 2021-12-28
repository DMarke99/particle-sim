#include "renderer.hpp"

int main() {
    int N = 1500;
    ParticleSimulator sim = ParticleSimulator(N);

    ParticleRenderer renderer = ParticleRenderer(
      800,
      800,
      sim
    );
    renderer.init();
    renderer.run();
    renderer.quit();
    return 0;
}