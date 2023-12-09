#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../component/PositionF.hpp"

struct Camera
{
    enum class Zoom
    {
        ZOOM_IN,
        ZOOM_OUT
    };

    PositionF position;
    PositionF velocity;
    PositionF view_port;
    const PositionF starting_view_port;
    float zoom = STARTING_ZOOM;
    constexpr static inline auto DEFAULT_VELOCITY = 1.F;
    constexpr static inline auto STARTING_ZOOM = 1.0F;
    constexpr static inline auto STARTING_VIEWPORT_SIZE_X = 64.0F;
    constexpr static inline auto ZOOM_DELTA = 0.01F;

    [[nodiscard]] bool inside_view_port(const PositionF & other_pos) const;
    void change_zoom(const Zoom & new_zoom);
};

#endif
