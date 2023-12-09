#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

#include <SDL2/SDL.h>

struct Color {
    uint8_t r, g, b, a;

    [[nodiscard]] SDL_Color sdl_color() const;

    constexpr inline static auto OPAQUE = 255;
    constexpr inline static auto SOLID = 255;
    constexpr inline static auto TRANSPARENT = 0;
    const static Color RED;
    const static Color GREEN;
    const static Color BLUE;
    const static Color WHITE;
    const static Color BLACK;
};

constexpr inline Color Color::RED = {SOLID, 0, 0, OPAQUE};
constexpr inline Color Color::GREEN = {0, SOLID, 0, OPAQUE};
constexpr inline Color Color::BLUE = {0, 0, SOLID, OPAQUE};
constexpr inline Color Color::WHITE = {SOLID, SOLID, SOLID, OPAQUE};
constexpr inline Color Color::BLACK = {0, 0, 0, OPAQUE};

#endif
