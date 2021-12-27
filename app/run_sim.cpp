#include "renderer.hpp"

int main() {
    int N = 20;
    ParticleSimulator sim = ParticleSimulator(N);

    ParticleRenderer renderer = ParticleRenderer(
      1200,
      900,
      sim
    );
    renderer.init();
    renderer.run();
    renderer.quit();
    return 0;
}