#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

#include <SDL2/SDL.h>

struct Color {
    uint8_t r, g, b, a;

    [[nodiscard]] static Color red();
    [[nodiscard]] static Color green();
    [[nodiscard]] static Color blue();
    [[nodiscard]] static Color white();
    [[nodiscard]] static Color black();

    [[nodiscard]] SDL_Color sdl_color() const;

    constexpr inline static auto OPAQUE = 255;
    constexpr inline static auto SOLID = 255;
    constexpr inline static auto TRANSPARENT = 0;
};

#endif
