#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "Color.hpp"
#include "GraphicsPrimitives.hpp"
#include "texture/Texture.hpp"
#include "../math/Angle.hpp"
#include "../component/Position.hpp"
#include "../component/PositionF.hpp"
#include "Camera.hpp"
#include "texture/TextureStorage.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

#include <SDL2/SDL.h>

#include <string>
#include <memory>

class Graphics
{
public:
    Graphics(const std::string & window_name, const TextureStorage::TextureConfig & texture_config);
    ~Graphics() = default;
    Graphics(Graphics&) = delete;
    Graphics(Graphics&&) = delete;
    Graphics operator=(Graphics) = delete;
    Graphics& operator=(Graphics&&) = delete;

    constexpr static int DEFAULT_TEXTURE_SIDE = 16;
private:
    [[nodiscard]] static SDL_DisplayMode create_display_mode();
public:
    void clear() const;
    void set_color(const Color & color = Color::white()) const;
    
    void draw_primitive(const GraphicsPrimitives::Point & point) const;
    void draw_primitive(const GraphicsPrimitives::Line & line) const;
    void draw_primitive(const GraphicsPrimitives::Rect & rect) const;
    void draw_primitive(const GraphicsPrimitives::RectFill & rect) const;
    void draw_primitive(const GraphicsPrimitives::Circle & circle) const;
    void draw_texture(const Texture & texture) const;
    void draw_texture(const Texture & texture, const GraphicsPrimitives::Point & position) const;
    void draw_texture(
        const Texture & texture,
        const GraphicsPrimitives::Point & position,
        const GraphicsPrimitives::Size & size
    ) const;
    void draw_texture(
        const Texture & texture,
        const GraphicsPrimitives::Point & position,
        const GraphicsPrimitives::Size & size,
        const Angle & angle
    ) const;

    void present() const;

    [[nodiscard]] PositionF screen_to_world(const Position & position) const;
    [[nodiscard]] Position world_to_screen(const PositionF & position) const;
    [[nodiscard]] Position world_to_screen(const Position & position) const;

    [[nodiscard]] int window_width() const noexcept;
    [[nodiscard]] int window_height() const noexcept;
    [[nodiscard]] Camera & camera() noexcept;
private:
    // DEPENDENCY ORDER
    SDL_DisplayMode m_display_mode;
    Window m_window;
    Renderer m_renderer;
    Camera m_camera;
public:
    TextureStorage texture_storage;
};

#endif
