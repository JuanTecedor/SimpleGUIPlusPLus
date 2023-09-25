#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>

struct Texture
{
public:
    explicit Texture(SDL_Texture * p_texture);
    ~Texture();
    Texture(Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture operator=(Texture) = delete;
    Texture& operator=(Texture&&) = delete;

    SDL_Texture * texture;
    const unsigned int w, h;
private:
    [[nodiscard]] static unsigned int getWidth(SDL_Texture * texture);
    [[nodiscard]] static unsigned int getHeight(SDL_Texture * texture);
};

#endif
