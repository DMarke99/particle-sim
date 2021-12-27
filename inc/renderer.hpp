#pragma once
#include "SDL.h" 
#include "simulation.hpp"
#include <array>

class ParticleRenderer {
    ParticleSimulator* simulator;
    size_t SCREEN_WIDTH;
    size_t SCREEN_HEIGHT;
    float SCALE_FACTOR;
    size_t MAX_FPS=60;

    Mat3d rot = {{1,0,0},{0,1,0},{0,0,1}};
    std::vector<std::array<Vec3d, 2>> frame;

	SDL_Renderer *renderer;
	SDL_Window *window;

    public:
        ParticleRenderer(
            const size_t& SCREEN_WIDTH, 
            const size_t& SCREEN_HEIGHT,
            ParticleSimulator &simulator
        );

        void init();

        void clear_screen();
        void draw_frame();
        void draw_particles();
        void render();

        void run();
        void quit();
};

std::vector<std::array<Vec3d, 2>> get_frame(const Vec3d& center, const float& width);