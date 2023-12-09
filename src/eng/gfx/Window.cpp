#include "Window.hpp"

#include "../util/Utils.hpp"

Window::Window(const std::string & name, const SDL_DisplayMode & display_mode) :
    window{
        SDL_CreateWindow(
            name.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            display_mode.w,
            display_mode.h,
            SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
        )
    }
{
    if(window == nullptr)
    {
        throw_sdl_error();
    }
}

Window::~Window()
{
    SDL_DestroyWindow(window);
}
