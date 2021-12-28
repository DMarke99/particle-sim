#include "renderer.hpp"

ParticleRenderer::ParticleRenderer(
    const size_t& SCREEN_WIDTH, 
    const size_t& SCREEN_HEIGHT,
    ParticleSimulator &simulator
): SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT) {
    this->simulator = &simulator;
    this->SCALE_FACTOR = 0.5 * std::min(SCREEN_WIDTH, SCREEN_HEIGHT) / simulator.width / this->SDL_SCALE;
    this->frame = get_frame(simulator.center, simulator.width);
}


void ParticleRenderer::init() {
    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow(
        "Particle Simulation",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        this->SCREEN_WIDTH,
        this->SCREEN_HEIGHT,
        0
    );

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderSetScale( this->renderer, this->SDL_SCALE, this->SDL_SCALE );

    SDL_SetRenderDrawBlendMode( this->renderer, SDL_BLENDMODE_BLEND);
}

void ParticleRenderer::rotate_view(const Rotation& rotation) {

    this->rot = get_rotation_matrix(rotation, 0.05) * this->rot;

}

void ParticleRenderer::clear_screen() {
    // Set render color to black ( background will be rendered in this color )
    SDL_SetRenderDrawColor( this->renderer, 0, 0, 0, 255 );

    // Clear window
    SDL_RenderClear( this->renderer );
}

void ParticleRenderer::draw_frame() {
    // Set render color to white 
    SDL_SetRenderDrawColor( this->renderer, 127, 127, 127, 255 );

    for (auto line : this->frame) {
        Vec3d p0 = this->rot * (line[0] - this->simulator->center) / this->simulator->width;
        Vec3d p1 = this->rot * (line[1] - this->simulator->center) / this->simulator->width;

        SDL_RenderDrawLine(this->renderer, 
            round(this->SCALE_FACTOR * p0.x + this->SCREEN_WIDTH/2/this->SDL_SCALE), 
            round(this->SCALE_FACTOR * p0.y + this->SCREEN_HEIGHT/2/this->SDL_SCALE),
            round(this->SCALE_FACTOR * p1.x + this->SCREEN_WIDTH/2/this->SDL_SCALE), 
            round(this->SCALE_FACTOR * p1.y + this->SCREEN_HEIGHT/2/this->SDL_SCALE)
        );
    }
}

void ParticleRenderer::draw_particles() {
    // Set render color to white 
    SDL_SetRenderDrawColor( this->renderer, 225, 255, 255, 95 );

    for (auto particle : this->simulator->particles) {
        Vec3d pos = this->rot * (particle.pos - this->simulator->center) / this->simulator->width;

        SDL_RenderDrawPoint(this->renderer, 
            round(this->SCALE_FACTOR * pos.x + this->SCREEN_WIDTH/2/this->SDL_SCALE), 
            round(this->SCALE_FACTOR * pos.y + this->SCREEN_HEIGHT/2/this->SDL_SCALE)
        );
    }
}

void ParticleRenderer::render() {

    // Clear window
    this->clear_screen();

    // Draws particles
    this->draw_particles();

    // Draws bounding box for particles
    this->draw_frame();
}


void ParticleRenderer::run() {

    // Clears window
    this->clear_screen();

    // Gets timers
    using namespace std::chrono;
    double avg_iter_duration = 0.0;
    double fps_denom = 0.0;
    float decay_const = 0.1;

    SDL_Event e;
    bool quit = false;
    while (!quit){

        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        while (SDL_PollEvent(&e)){
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_UP: 
                            this->rotate_view(Rotation::up); 
                            break;
                        case SDLK_DOWN: 
                            this->rotate_view(Rotation::down);
                            break;
                        case SDLK_LEFT: 
                            this->rotate_view(Rotation::left);
                            break;
                        case SDLK_RIGHT: 
                            this->rotate_view(Rotation::right);
                            break;
                    }
                    break;
            }

        }

        // Runs one step of the simulation
        this->simulator->step();

        // Draws screen elements
        this->render();

        // Render the rect to the screen
        SDL_RenderPresent( this->renderer);

        // Estimates FPS
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

        avg_iter_duration += decay_const * (time_span.count() - avg_iter_duration);
        fps_denom += decay_const * (1 - fps_denom);

        int FPS = floor(fps_denom/avg_iter_duration);
        std::string new_title = "Particle Simulation - FPS: " +  std::to_string(FPS);
        SDL_SetWindowTitle( this->window, new_title.c_str());
    }
}

void ParticleRenderer::quit() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

std::vector<std::array<Vec3d, 2>> get_frame(const Vec3d& center, const float& width) {
    std::vector<std::array<Vec3d, 2>> res = {};
    res.push_back({Vec3d({1,1,1}), Vec3d({-1,1,1})});
    res.push_back({Vec3d({1,-1,1}), Vec3d({-1,-1,1})});
    res.push_back({Vec3d({1,1,-1}), Vec3d({-1,1,-1})});
    res.push_back({Vec3d({1,-1,-1}), Vec3d({-1,-1,-1})});
    res.push_back({Vec3d({1,1,1}), Vec3d({1,-1,1})});
    res.push_back({Vec3d({-1,1,1}), Vec3d({-1,-1,1})});
    res.push_back({Vec3d({1,1,-1}), Vec3d({1,-1,-1})});
    res.push_back({Vec3d({-1,1,-1}), Vec3d({-1,-1,-1})});
    res.push_back({Vec3d({1,1,1}), Vec3d({1,1,-1})});
    res.push_back({Vec3d({-1,1,1}), Vec3d({-1,1,-1})});
    res.push_back({Vec3d({1,-1,1}), Vec3d({1,-1,-1})});
    res.push_back({Vec3d({-1,-1,1}), Vec3d({-1,-1,-1})});

    std::for_each(
        res.begin(), 
        res.end(), 
        [center, width](std::array<Vec3d, 2> &line){ 
            line[0] *= width/2; line[0] += center;
            line[1] *= width/2; line[1] += center;
        }
    );

    return res;
}

Mat3d get_rotation_matrix(const Rotation& rotation, const float& theta) {
    switch (rotation) {
        case Rotation::left:
            return {{cos(theta), 0, -sin(theta)}, {0,1,0}, {sin(theta), 0, cos(theta)}};
        case Rotation::right:
            return {{cos(theta), 0, sin(theta)}, {0,1,0}, {-sin(theta), 0, cos(theta)}};
        case Rotation::up:
            return {{1,0,0}, {0, cos(theta), -sin(theta)}, {0, sin(theta), cos(theta)}};
        case Rotation::down:
            return {{1,0,0}, {0, cos(theta), sin(theta)}, {0, -sin(theta), cos(theta)}};
        case Rotation::anticlockwise:
            return {{cos(theta), sin(theta), 0}, {-sin(theta), cos(theta),0}, {0,0,1}};
        case Rotation::clockwise:
            return {{cos(theta), -sin(theta), 0}, {sin(theta), cos(theta),0}, {0,0,1}};
        default:
            return {{1,0,0},{0,1,0},{0,0,1}};
    }
}