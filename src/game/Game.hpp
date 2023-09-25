#ifndef GAME_HPP
#define GAME_HPP

#include "../eng/Engine.hpp"
#include "World.hpp"

class Game
{
public:
    explicit Game(const EngineConfig & engine_config);
    void run();
private:
    void handle_events();
    void handle_move_camera(const MoveCameraEvent & move_camera_event);
    void handle_move_player(const MovePlayerEvent & move_player_event);
    void update(const TimeStep::delta_type & delta_time);
    void update_second();
    void draw();

    bool m_running = true;
    Engine m_engine;
    World m_world;
};

#endif
