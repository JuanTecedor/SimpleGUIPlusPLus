#include "EventHandler.hpp"

#include <SDL2/SDL.h>

#include <span>

std::vector<Event> EventHandler::events()
{
    std::vector<Event> events;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (auto type = event.type; type == SDL_QUIT)
        {
            return {ExitEvent{}};
        }
    }

    SDL_PumpEvents();
    int size = 0;
    const Uint8 * state = SDL_GetKeyboardState(&size);
    auto state_span = std::span(state, static_cast<std::size_t>(size));
    if(static_cast<bool>(state_span[SDL_SCANCODE_RIGHT]))
    {
        events.emplace_back(MovePlayerEvent{Direction::RIGHT});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_DOWN]))
    {
        events.emplace_back(MovePlayerEvent{Direction::DOWN});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_LEFT]))
    {
        events.emplace_back(MovePlayerEvent{Direction::LEFT});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_UP]))
    {
        events.emplace_back(MovePlayerEvent{Direction::UP});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_A]))
    {
        events.emplace_back(MoveCameraEvent{Direction::LEFT});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_S]))
    {
        events.emplace_back(MoveCameraEvent{Direction::DOWN});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_D]))
    {
        events.emplace_back(MoveCameraEvent{Direction::RIGHT});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_W]))
    {
        events.emplace_back(MoveCameraEvent{Direction::UP});
    }
    return events;
}
