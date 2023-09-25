#include <algorithm>
#include <cassert>
#include <stdexcept>

#include "TextureStorage.hpp"
#include "TextureLoader.hpp"

TextureStorage::TextureStorage(SDL_Renderer * renderer, [[maybe_unused]] const TextureConfig & texture_config)
{
    for(const auto & texture_path : texture_config.texture_paths)
    {
        auto * texture = new Texture{TextureLoader::load_png(renderer, texture_config.base_path / texture_path.path)};
        m_textures.emplace(texture_path.texture_name, texture);
        if(texture->texture == nullptr)
        {
            throw std::runtime_error("At least one texture is nullptr");
        }
    }
    auto * texture = new Texture{TextureLoader::error_texture(renderer)};
    m_textures.emplace("error", texture);
    if(texture->texture == nullptr)
    {
        throw std::runtime_error("At least one texture is nullptr");
    }
}

Texture & TextureStorage::get([[maybe_unused]] const std::string & texture_type)
{
    assert(m_textures.contains(texture_type));
    return *m_textures[texture_type];
}
