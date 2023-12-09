#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP

#include <string>
#include <unordered_map>
#include <filesystem>
#include <vector>
#include <functional>
#include <memory>
#include <string_view>
#include <optional>

#include <SDL2/SDL.h>

#include "Texture.hpp"

class TextureStorage
{
public:
    struct TextureConfig
    {
        std::optional<std::filesystem::path> base_path = std::nullopt;
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

    Texture * get(const std::string & texture_type);

    constexpr static inline std::string ERROR_TEXTURE = "ERROR";
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
};

#endif
