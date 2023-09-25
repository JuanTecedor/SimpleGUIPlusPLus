#include "Utils.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdexcept>

void throw_sdl_error()
{
    throw std::runtime_error(SDL_GetError());
}

void throw_sdl_image_error()
{
    throw std::runtime_error(IMG_GetError());
}
