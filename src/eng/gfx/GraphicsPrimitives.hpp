#ifndef GRAPHICS_PRIMITIVES_HPP
#define GRAPHICS_PRIMITIVES_HPP

#include "../component/Position.hpp"

namespace GraphicsPrimitives {

using Point = Position;

using Size = Vector2i;

struct Line
{
    Point origin;
    Point destination;
};

struct Rect
{
    Position center;
    Size size;
};

struct RectFill
{
    Position center;
    Size size;
};

struct Circle
{
    Point center;
    int radius = 0;
};

}

#endif
