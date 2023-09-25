#include "TextureLoader.hpp"

#include <SDL2/SDL_image.h>

#include "../../util/Utils.hpp"
#include "../Color.hpp"

Texture TextureLoader::load_png(SDL_Renderer * renderer, const std::filesystem::path & path)
{
    if(!std::filesystem::exists(path))
    {
        throw_sdl_error();
    }
    SDL_Surface * surface = IMG_Load(path.c_str());
    if(surface == nullptr)
    {
        SDL_FreeSurface(surface);
        throw_sdl_image_error();
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == nullptr)
    {
        throw_sdl_error();
    }

    SDL_FreeSurface(surface);
    
    return Texture{texture};
}

Texture TextureLoader::error_texture(SDL_Renderer * renderer)
{
    constexpr auto side = 32;
    constexpr auto depth = 32;
    SDL_Surface * surface = SDL_CreateRGBSurface(0, side, side, depth, 0, 0, 0, 0);
    constexpr auto stripes = 10;
    for(int i = 0; i <= stripes; i += 2)
    {
        SDL_Rect rect = {
            surface->w / stripes * i,
            0,
            surface->w / stripes,
            surface->h
        };
        Color color {Color::SOLID, 0, Color::SOLID, Color::OPAQUE};
        SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == nullptr)
    {
        throw_sdl_error();
    }

    SDL_FreeSurface(surface);

    return Texture{texture};
}
