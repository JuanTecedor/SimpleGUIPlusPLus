#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP

#include <string>
#include <unordered_map>
#include <filesystem>
#include <vector>
#include <functional>
#include <memory>

#include <SDL2/SDL.h>

#include "Texture.hpp"

class TextureStorage
{
public:
    using TexturePath = struct {
        std::string texture_name;
        std::filesystem::path path;
    };
    using TexturePaths = std::vector<TexturePath>;
    using TextureConfig = struct {
        std::filesystem::path & base_path;
        TexturePaths texture_paths;
    };

    explicit TextureStorage(
        SDL_Renderer * renderer,
        const TextureConfig & texture_config
    );

    ~TextureStorage() = default;
    TextureStorage(TextureStorage&) = delete;
    TextureStorage(TextureStorage&&) = delete;
    TextureStorage operator=(TextureStorage) = delete;
    TextureStorage& operator=(TextureStorage&&) = delete;

    Texture & get(const std::string & texture_type);
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
};

#endif
