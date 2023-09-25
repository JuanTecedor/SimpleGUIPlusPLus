#include "System.hpp"

#include "util/Utils.hpp"

#include <SDL2/SDL.h>

System::System()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw_sdl_error();
    }
}

System::~System()
{
    SDL_Quit();
}
