#include "Color.hpp"

[[nodiscard]] Color Color::red()
{
    return Color{SOLID, 0, 0, OPAQUE};
}

[[nodiscard]] Color Color::green()
{
    return Color{0, SOLID, 0, OPAQUE};
}

[[nodiscard]] Color Color::blue()
{
    return Color{0, 0, SOLID, OPAQUE};
}

[[nodiscard]] Color Color::white()
{
    return Color{SOLID, SOLID, SOLID, OPAQUE};
}

[[nodiscard]] Color Color::black()
{
    return Color{0, 0, 0, OPAQUE};
}

[[nodiscard]] SDL_Color Color::sdl_color() const
{
    return SDL_Color{r, g, b, a};
}
