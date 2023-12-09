#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <filesystem>

#include "TextureStorage.hpp"
#include "TextureLoader.hpp"

TextureStorage::TextureStorage(SDL_Renderer * renderer, const TextureConfig & texture_config)
{
    if(texture_config.base_path.has_value())
    {
        auto base_path = texture_config.base_path.value();
        for(const auto & directory_entry : std::filesystem::directory_iterator(base_path))
        {
            if(!directory_entry.is_regular_file()) {
                continue;
            }
            auto file_name = directory_entry.path().filename();
            auto * texture = new Texture{
                TextureLoader::load_png(
                    renderer,
                    base_path / file_name)
            };
            if(m_textures.contains(file_name))
            {
                assert(false);  // The texture is duplicated
            }
            m_textures.emplace(file_name.replace_extension(), texture);
            if(texture->texture == nullptr)
            {
                throw std::runtime_error("At least one texture is nullptr");
            }
        }
    }

    auto * texture = new Texture{TextureLoader::error_texture(renderer)};
    m_textures.emplace(ERROR_TEXTURE, texture);
    if(texture->texture == nullptr)
    {
        throw std::runtime_error("At least one texture is nullptr");
    }
}

Texture * TextureStorage::get(const std::string & texture_type)
{
    assert(m_textures.contains(texture_type));
    return m_textures[texture_type].get();
}
