#ifndef UTILS_HPP
#define UTILS_HPP

void throw_sdl_error();

void throw_sdl_image_error();

template <typename... T>
constexpr bool always_false = false;

#endif
