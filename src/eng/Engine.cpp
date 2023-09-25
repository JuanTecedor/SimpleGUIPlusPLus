#include "Engine.hpp"
#include "util/Utils.hpp"

#include <SDL2/SDL.h>

Engine::Engine(const EngineConfig & engine_config) :
    graphics{engine_config.app_name, engine_config.texture_config}
{
}
