#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>

#include <string>

struct Window
{
    Window(const std::string & name, const SDL_DisplayMode & display_mode);
    ~Window();
    Window(Window&) = delete;
    Window(Window&&) = delete;
    Window operator=(Window) = delete;
    Window& operator=(Window&&) = delete;

    SDL_Window * window;
};

#endif
