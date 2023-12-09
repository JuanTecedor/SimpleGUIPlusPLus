#ifndef EVENT_HPP
#define EVENT_HPP

#include "../component/Direction.hpp"

#include <variant>

struct ExitEvent{};

// TODO, pack the following two in one?

struct ArroyKeysEvent
{
    Direction direction;
};

struct WASDKeysEvent
{
    Direction direction;
};

struct MouseWheelEvent
{
    int y;
};

struct MouseMotionEvent
{
    int x;
    int y;
};

struct LeftMouseClickEvent
{
    int x;
    int y;
};

using Event = std::variant<
    ExitEvent,
    ArroyKeysEvent,
    WASDKeysEvent,
    MouseWheelEvent,
    MouseMotionEvent,
    LeftMouseClickEvent
>;

#endif
