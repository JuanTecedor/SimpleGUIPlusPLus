#include "Game.hpp"

#include <cassert>

Game::Game(const EngineConfig & engine_config) :
    m_engine{engine_config}
{
}

void Game::run()
{
    while(true)
    {
        m_engine.time_step.tick();

        handle_events();

        if(!m_running)
        {
            break;
        }

        while(!m_engine.time_step.done())
        {
            auto delta = m_engine.time_step.delta_time();
            if(m_engine.time_step.second_passed())
            {
                update_second();
            }
            update(delta);
            m_engine.time_step.advance();
        }
        draw();
    }
}

void Game::handle_events()
{
    auto events = m_engine.event_handler.events();
    for (const auto & event : events)
    {
        if(std::holds_alternative<ExitEvent>(event))
        {
            m_running = false;
            return;
        }
        else if(std::holds_alternative<MoveCameraEvent>(event))
        {
            handle_move_camera(std::get<MoveCameraEvent>(event));
        }
        else if(std::holds_alternative<MovePlayerEvent>(event))
        {
            handle_move_player(std::get<MovePlayerEvent>(event));
        }
        else
        {
            assert(false);
        }
    }
}

void Game::handle_move_camera(const MoveCameraEvent & move_camera_event)
{
    const auto & direction = move_camera_event.direction;
    if(direction == Direction::DOWN)
    {
        m_engine.graphics.camera().velocity.y -= Camera::DEFAULT_VELOCITY;
    }
    else if(direction == Direction::RIGHT)
    {
        m_engine.graphics.camera().velocity.x += Camera::DEFAULT_VELOCITY;
    }
    else if(direction == Direction::LEFT)
    {
        m_engine.graphics.camera().velocity.x -= Camera::DEFAULT_VELOCITY;
    }
    else if(direction == Direction::UP)
    {
        m_engine.graphics.camera().velocity.y += Camera::DEFAULT_VELOCITY;
    }
    else
    {
        assert(false);
    }
}

void Game::handle_move_player(const MovePlayerEvent & move_player_event)
{
    const auto & direction = move_player_event.direction;
    if(direction == Direction::DOWN)
    {
        m_world.player.velocity.y -= Player::DEFAULT_VELOCITY;
    }
    else if(direction == Direction::RIGHT)
    {
        m_world.player.velocity.x += Player::DEFAULT_VELOCITY;
    }
    else if(direction == Direction::LEFT)
    {
        m_world.player.velocity.x -= Player::DEFAULT_VELOCITY;
    }
    else if(direction == Direction::UP)
    {
        m_world.player.velocity.y += Player::DEFAULT_VELOCITY;
    }
    else
    {
        assert(false);
    }
}

void Game::update(const TimeStep::delta_type & delta_time)
{
    m_world.player.position += m_world.player.velocity * delta_time;
    m_world.player.velocity = {};

    m_engine.graphics.camera().position += m_engine.graphics.camera().velocity * delta_time;
    m_engine.graphics.camera().velocity = {};
}

void Game::update_second()
{
    constexpr auto rotation = Angle::from_degrees(5.F);
    m_world.rect.angle += rotation;
}

void Game::draw()
{
    auto & graphics = m_engine.graphics;
    graphics.set_color();
    graphics.clear();

    // Draw player-rect line
    graphics.set_color(Color::green());
    graphics.draw_primitive(GraphicsPrimitives::Line{
        .origin=graphics.world_to_screen(m_world.player.position),
        .destination=graphics.world_to_screen(m_world.rect.position)
    });

    // Draw player
    {
        constexpr auto player_radious = 50;
        graphics.set_color(Color::blue());
        graphics.draw_primitive(GraphicsPrimitives::Circle{
            .center=graphics.world_to_screen(m_world.player.position),
            .radius=player_radious
        });
    }

    // Draw rect
    {
        constexpr auto size = GraphicsPrimitives::Size{200, 250};
        graphics.draw_texture(
            graphics.texture_storage.get("red"),
            graphics.world_to_screen(m_world.rect.position),
            size,
            m_world.rect.angle
        );
    }

    // Draw error
    {
        constexpr auto position = GraphicsPrimitives::Point{500, 600};
        constexpr auto size = GraphicsPrimitives::Size{100, 100};
        graphics.draw_texture(
            graphics.texture_storage.get("error"),
            position,
            size
        );
    }

    graphics.present();
}
