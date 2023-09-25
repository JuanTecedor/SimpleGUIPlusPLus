#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "System.hpp"
#include "event/EventHandler.hpp"
#include "time/TimeStep.hpp"
#include "gfx/Graphics.hpp"
#include "EngineConfig.hpp"

class Engine
{
public:
    explicit Engine(const EngineConfig & engine_config);
    ~Engine() = default;
    Engine(Engine &) = delete;
    Engine(Engine &&) = delete;
    Engine operator=(Engine) = delete;
    Engine& operator=(Engine&&) = delete;

    // ORDER DEPENDENCY, System must init SDL first
    System system;
    Graphics graphics;
    EventHandler event_handler = {};
    TimeStep time_step;
};

#endif
