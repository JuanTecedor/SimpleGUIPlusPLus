#include "Graphics.hpp"

#include "../util/Utils.hpp"

#include <utility>
#include <cmath>

Graphics::Graphics(const std::string & window_name, const TextureStorage::TextureConfig & texture_config) :
    m_display_mode{create_display_mode()},
    m_window{window_name, m_display_mode},
    m_renderer{m_window.window},
    m_camera{
        .position{0, 0},
        .velocity{0, 0},
        .view_port{
            Camera::STARTING_VIEWPORT_SIZE_X,
            Camera::STARTING_VIEWPORT_SIZE_X * static_cast<float>(window_height()) / static_cast<float>(window_width())
        },
        .starting_view_port{
            Camera::STARTING_VIEWPORT_SIZE_X,
            Camera::STARTING_VIEWPORT_SIZE_X * static_cast<float>(window_height()) / static_cast<float>(window_width())
        },
        .zoom=Camera::STARTING_ZOOM 
    },
    texture_storage{m_renderer.renderer, texture_config}
{
}

SDL_DisplayMode Graphics::create_display_mode()
{
    SDL_DisplayMode display_mode;
    if(SDL_GetDesktopDisplayMode(0, &display_mode) < 0)
    {
        throw_sdl_error();
    }
    return display_mode;
}

void Graphics::clear() const
{
    SDL_RenderClear(m_renderer.renderer);
}

void Graphics::set_color(const Color & color) const
{
    auto sdl_color = color.sdl_color();
    SDL_SetRenderDrawColor(m_renderer.renderer, sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
}

void Graphics::draw_primitive(const GraphicsPrimitives::Point & point) const
{
    SDL_RenderDrawPoint(
        m_renderer.renderer, 
        point.x,
        point.y
    );
}

void Graphics::draw_primitive(const GraphicsPrimitives::Line & line) const
{
    SDL_RenderDrawLine(
        m_renderer.renderer,
        line.origin.x,
        line.origin.y,
        line.destination.x,
        line.destination.y
    );
}

void Graphics::draw_primitive(const GraphicsPrimitives::Rect & rect) const
{
    auto sdl_rect = SDL_Rect{
        .x=rect.center.x - rect.size.x / 2,
        .y=rect.center.y - rect.size.y / 2,
        .w=rect.size.x,
        .h=rect.size.y
    };
    SDL_RenderDrawRect(
        m_renderer.renderer,
        &sdl_rect
    );
}

void Graphics::draw_primitive(const GraphicsPrimitives::RectFill & rect) const
{
    auto sdl_rect = SDL_Rect{
        .x=rect.center.x - rect.size.x / 2,
        .y=rect.center.y - rect.size.y / 2,
        .w=rect.size.x,
        .h=rect.size.y
    };
    SDL_RenderFillRect(
        m_renderer.renderer,
        &sdl_rect
    );
}

void Graphics::draw_primitive(const GraphicsPrimitives::Circle & circle) const
{
    const auto & radius = circle.radius;
    for(int y_coord = -radius; y_coord <= radius; ++y_coord)
    {
        for(int x_coord = -radius; x_coord <= radius; ++x_coord)
        {
            if(x_coord * x_coord + y_coord * y_coord <= radius * radius)
            {
                SDL_RenderDrawPoint(
                    m_renderer.renderer,
                    circle.center.x + x_coord,
                    circle.center.y + y_coord
                );
            }
        }
    }
}

void Graphics::draw_texture(const Texture & texture) const
{
    SDL_Rect src = { 0, 0, static_cast<int>(texture.w), static_cast<int>(texture.h) };
    SDL_RenderCopy(m_renderer.renderer, texture.texture, &src, nullptr);
}

void Graphics::draw_texture(const Texture & texture, const GraphicsPrimitives::Point & position) const
{
    SDL_Rect src = { 0, 0, static_cast<int>(texture.w), static_cast<int>(texture.h) };
    SDL_Rect dst = {
        position.x - static_cast<int>(texture.w) / 2,
        position.y - static_cast<int>(texture.h) / 2,
        static_cast<int>(texture.w),
        static_cast<int>(texture.h)
    };
    SDL_RenderCopy(m_renderer.renderer, texture.texture, &src, &dst);
}

void Graphics::draw_texture(
    const Texture & texture,
    const GraphicsPrimitives::Point & position,
    const GraphicsPrimitives::Size & size) const
{
    SDL_Rect src = { 0, 0, static_cast<int>(texture.w), static_cast<int>(texture.h) };
    SDL_Rect dst = {
        position.x - size.x / 2,
        position.y - size.y / 2,
        size.x,
        size.y
    };
    SDL_RenderCopy(m_renderer.renderer, texture.texture, &src, &dst);
}

void Graphics::draw_texture(
    const Texture & texture,
    const GraphicsPrimitives::Point & position,
    const GraphicsPrimitives::Size & size,
    const Angle & angle) const
{
    SDL_Rect src = { 0, 0, static_cast<int>(texture.w), static_cast<int>(texture.h) };
    SDL_Rect dst = {
        position.x - size.x / 2,
        position.y - size.y / 2,
        size.x,
        size.y
    };
    SDL_RenderCopyEx(
        m_renderer.renderer,
        texture.texture,
        &src,
        &dst,
        static_cast<double>(angle.as_degrees()),
        nullptr,
        SDL_FLIP_NONE
    );
}

void Graphics::present() const
{
    SDL_RenderPresent(m_renderer.renderer);
}

PositionF Graphics::screen_to_world(const Position & position) const
{
    auto screen_pos = Position{
        position.x,
        window_height() - position.y
    };
    auto percent_screen = PositionF{
        static_cast<float>(screen_pos.x) / static_cast<float>(window_width()),
        static_cast<float>(screen_pos.y) / static_cast<float>(window_height())
    };
    auto result_world_delta = PositionF{
        percent_screen.x * m_camera.view_port.x,
        percent_screen.y * m_camera.view_port.y
    };
    auto res = result_world_delta + m_camera.position - m_camera.view_port / 2;
    assert(m_camera.inside_view_port(res));
    return res;
}

Position Graphics::world_to_screen(const PositionF & position) const
{
    auto delta = position - m_camera.position;
    auto delta_view_port = PositionF{
        delta.x + (m_camera.view_port.x / 2),
        delta.y + (m_camera.view_port.y / 2)
    };
    auto percent_view_port = PositionF{
        delta_view_port.x / m_camera.view_port.x,
        delta_view_port.y / m_camera.view_port.y
    };
    auto pos = Position{
        static_cast<int>(static_cast<float>(window_width()) * percent_view_port.x),
        window_height() - static_cast<int>(static_cast<float>(window_height()) * percent_view_port.y)
    };
    auto res = Position{
        pos.x,
        pos.y
    };
    return res;
}

Position Graphics::world_to_screen(const Position & position) const
{
    return world_to_screen(PositionF{position});
}

int Graphics::window_width() const noexcept
{
    return m_display_mode.w;
}

int Graphics::window_height() const noexcept
{
    return m_display_mode.h;
}

Camera & Graphics::camera() noexcept
{
    return m_camera;
}
