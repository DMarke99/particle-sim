#include "renderer.hpp"

ParticleRenderer::ParticleRenderer(
    const size_t& SCREEN_WIDTH, 
    const size_t& SCREEN_HEIGHT,
    ParticleSimulator &simulator
): SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT) {
    this->simulator = &simulator;
    this->SCALE_FACTOR = 0.25 * std::min(SCREEN_WIDTH, SCREEN_HEIGHT) / simulator.width;
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
}

void ParticleRenderer::clear_screen() {
    // Set render color to black ( background will be rendered in this color )
    SDL_SetRenderDrawColor( this->renderer, 0, 0, 0, 255 );

    // Clear window
    SDL_RenderClear( this->renderer );
}

void ParticleRenderer::draw_frame() {
    // Set render color to white 
    SDL_SetRenderDrawColor( this->renderer, 225, 255, 255, 255 );

    for (auto line : this->frame) {
        Vec3d p0 = this->rot * (line[0] - this->simulator->center) / this->simulator->width;
        Vec3d p1 = this->rot * (line[1] - this->simulator->center) / this->simulator->width;

        SDL_RenderDrawLine(this->renderer, 
            round(this->SCALE_FACTOR * p0.x + this->SCREEN_WIDTH/2), 
            round(this->SCALE_FACTOR * p0.y + this->SCREEN_HEIGHT/2),
            round(this->SCALE_FACTOR * p1.x + this->SCREEN_WIDTH/2), 
            round(this->SCALE_FACTOR * p1.y + this->SCREEN_HEIGHT/2)
        );
    }
}

void ParticleRenderer::draw_particles() {
    // Set render color to white 
    SDL_SetRenderDrawColor( this->renderer, 225, 255, 255, 127 );

    for (auto particle : this->simulator->particles) {
        Vec3d pos = this->rot * particle.pos;

        SDL_RenderDrawPoint(this->renderer, 
            round(this->SCALE_FACTOR * pos.x + this->SCREEN_WIDTH/2), 
            round(this->SCALE_FACTOR * pos.y + this->SCREEN_HEIGHT/2)
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

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( this->renderer, 0, 0, 255, 255 );

    // Render rect
    SDL_RenderFillRect( this->renderer, &r );

    int i = 0;
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }

        // Runs one step of the simulation
        this->simulator->step();

        // Draws screen elements
        this->render();

        //std::cout << ++i << std::endl;
        if (i == 10) quit = true;
        // Render the rect to the screen
        SDL_RenderPresent( this->renderer);
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
