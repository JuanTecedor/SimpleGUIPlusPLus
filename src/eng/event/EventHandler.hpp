#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "Event.hpp"

#include <SDL2/SDL.h>

#include <vector>

class EventHandler
{
public:
    [[nodiscard]] static std::vector<Event> events();
private:
    static void handle_keyboard_events(std::vector<Event> & events);
    static void handle_mouse_wheel_event(
        std::vector<Event> & events,
        const SDL_MouseWheelEvent & mouse_wheel_event
    );
    static void handle_mouse_motion_event(
        std::vector<Event> & events,
        const SDL_MouseMotionEvent & mouse_motion_event
    );
    static void handle_mouse_button_up(
        std::vector<Event> & events,
        const SDL_MouseButtonEvent & mouse_button_event
    );
};

#endif
