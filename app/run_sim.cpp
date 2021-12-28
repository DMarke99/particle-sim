#include "renderer.hpp"

int main() {
    int N = 2500;
    ParticleSimulator sim = ParticleSimulator(N);

    ParticleRenderer renderer = ParticleRenderer(
      600,
      600,
      sim
    );
    renderer.init();
    renderer.run();
    renderer.quit();
    return 0;
}