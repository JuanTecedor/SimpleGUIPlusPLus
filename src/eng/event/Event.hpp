#ifndef EVENT_HPP
#define EVENT_HPP

#include "../component/Direction.hpp"

#include <variant>

struct ExitEvent{};
struct MoveCameraEvent
{
    Direction direction;
};

struct MovePlayerEvent
{
    Direction direction;
};

using Event = std::variant<
    ExitEvent,
    MoveCameraEvent,
    MovePlayerEvent
>;

#endif
