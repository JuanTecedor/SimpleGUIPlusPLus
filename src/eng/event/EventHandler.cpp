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
        else if(type == SDL_MOUSEWHEEL)
        {
            handle_mouse_wheel_event(events, event.wheel);
        }
        else if(type == SDL_MOUSEBUTTONUP)
        {
            handle_mouse_button_up(events, event.button);
        }
        else if(type == SDL_MOUSEMOTION)
        {
            handle_mouse_motion_event(events, event.motion);
        }
    }
    handle_keyboard_events(events);
    return events;
}

void EventHandler::handle_keyboard_events(std::vector<Event> & events)
{
    SDL_PumpEvents();
    int size = 0;
    const Uint8 * state = SDL_GetKeyboardState(&size);
    auto state_span = std::span(state, static_cast<std::size_t>(size));
    if(static_cast<bool>(state_span[SDL_SCANCODE_RIGHT]))
    {
        events.emplace_back(ArroyKeysEvent{Direction::RIGHT});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_DOWN]))
    {
        events.emplace_back(ArroyKeysEvent{Direction::DOWN});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_LEFT]))
    {
        events.emplace_back(ArroyKeysEvent{Direction::LEFT});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_UP]))
    {
        events.emplace_back(ArroyKeysEvent{Direction::UP});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_A]))
    {
        events.emplace_back(WASDKeysEvent{Direction::LEFT});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_S]))
    {
        events.emplace_back(WASDKeysEvent{Direction::DOWN});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_D]))
    {
        events.emplace_back(WASDKeysEvent{Direction::RIGHT});
    }
    if(static_cast<bool>(state_span[SDL_SCANCODE_W]))
    {
        events.emplace_back(WASDKeysEvent{Direction::UP});
    }
}

void EventHandler::handle_mouse_wheel_event(
    std::vector<Event> & events,
    const SDL_MouseWheelEvent & mouse_wheel_event
)
{
    events.emplace_back(MouseWheelEvent{.y=mouse_wheel_event.y});
}

void EventHandler::handle_mouse_motion_event(
        std::vector<Event> & events,
        const SDL_MouseMotionEvent & mouse_motion_event
)
{
    events.emplace_back(MouseMotionEvent{.x=mouse_motion_event.x, .y=mouse_motion_event.y});
}

void EventHandler::handle_mouse_button_up(
    std::vector<Event> & events,
    const SDL_MouseButtonEvent & mouse_button_event
)
{
    if(mouse_button_event.button == SDL_BUTTON_LEFT)
    {
        events.emplace_back(LeftMouseClickEvent{
            .x=mouse_button_event.x,
            .y=mouse_button_event.y
        });
    }
}
