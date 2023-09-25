#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>

struct Renderer
{
    explicit Renderer(SDL_Window * window);
    ~Renderer();
    Renderer(Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer operator=(Renderer) = delete;
    Renderer& operator=(Renderer&&) = delete;

    SDL_Renderer * renderer;
};

#endif
