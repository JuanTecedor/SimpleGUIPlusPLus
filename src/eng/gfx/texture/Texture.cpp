#include "Texture.hpp"

#include <cassert>

Texture::Texture(SDL_Texture * p_texture) :
    texture{p_texture}, w{getWidth(texture)}, h{getHeight(texture)}
{
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}

[[nodiscard]] unsigned int Texture::getWidth(SDL_Texture * texture)
{
    int res = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &res, nullptr);
    assert(res > 0);
    return static_cast<unsigned int>(res);
}

[[nodiscard]] unsigned int Texture::getHeight(SDL_Texture * texture)
{
    int res = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &res);
    assert(res > 0);
    return static_cast<unsigned int>(res);
}
