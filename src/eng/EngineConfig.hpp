#ifndef ENGINE_CONFIG_HPP
#define ENGINE_CONFIG_HPP

#include "gfx/texture/TextureStorage.hpp"

#include <string>

struct EngineConfig
{
    std::string app_name;
    TextureStorage::TextureConfig texture_config;
};

#endif
