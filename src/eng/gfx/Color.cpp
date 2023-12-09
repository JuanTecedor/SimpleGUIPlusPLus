#include "Color.hpp"

[[nodiscard]] SDL_Color Color::sdl_color() const
{
    return SDL_Color{r, g, b, a};
}
