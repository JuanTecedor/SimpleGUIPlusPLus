#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include <filesystem>

#include <SDL2/SDL.h>

#include "Texture.hpp"

class TextureLoader
{
public:
    static Texture load_png(SDL_Renderer * renderer, const std::filesystem::path & path);
    static Texture error_texture(SDL_Renderer * renderer);
};

#endif
