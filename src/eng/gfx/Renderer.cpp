#include "Renderer.hpp"

#include "../util/Utils.hpp"

Renderer::Renderer(SDL_Window * window) :
    renderer{
        SDL_CreateRenderer(window, 1, SDL_RENDERER_PRESENTVSYNC)
    }
{
    if(renderer == nullptr)
    {
        throw_sdl_error();
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
}
