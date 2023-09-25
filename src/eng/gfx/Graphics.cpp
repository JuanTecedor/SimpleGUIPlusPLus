#include "Graphics.hpp"

#include "../util/Utils.hpp"

#include <utility>
#include <cmath>

Graphics::Graphics(const std::string & window_name, const TextureStorage::TextureConfig & texture_config) :
    m_display_mode{create_display_mode()},
    m_window{window_name, m_display_mode},
    m_renderer{m_window.window},
    m_camera{{0, 0}, {0, 0}},
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
    auto res = PositionF{position};
    auto window_transform = PositionF{
        static_cast<float>(window_width()) / 2,
        static_cast<float>(window_height()) / 2
    };
    res -= window_transform;
    res.y *= -1;
    res = res + m_camera.position;
    return res;
}

Position Graphics::world_to_screen(const PositionF & position) const
{
    return world_to_screen(Position{
        static_cast<int>(std::round(position.x)),
        static_cast<int>(std::round(position.y))
    });
}

Position Graphics::world_to_screen(const Position & position) const
{
    auto window_transform = PositionF{
        static_cast<float>(window_width()) / 2,
        static_cast<float>(window_height()) / 2
    };
    auto res = Position{PositionF{position} - m_camera.position + window_transform};
    res.y *= -1;
    res.y += window_height();
    return res;
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
