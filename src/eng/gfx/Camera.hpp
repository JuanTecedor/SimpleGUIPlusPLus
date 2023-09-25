#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../component/PositionF.hpp"

struct Camera
{
    PositionF position;
    PositionF velocity;
    constexpr static inline auto DEFAULT_VELOCITY = 500.F;
};

#endif
