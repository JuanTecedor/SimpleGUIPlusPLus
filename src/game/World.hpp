#ifndef WORLD_HPP
#define WORLD_HPP

#include "../eng/component/PositionF.hpp"
#include "../eng/math/Angle.hpp"

struct RotatingRect
{
    constexpr static PositionF starting_pos = {50.F, 200.F};
    PositionF position = starting_pos;
    Angle angle = Angle::from_degrees(0.F);
};

struct Player
{
    constexpr static PositionF starting_pos = {300.F, 250.F};
    PositionF position = starting_pos;
    PositionF velocity = {};
    constexpr static inline auto DEFAULT_VELOCITY = 200.F;
};

struct World
{
    RotatingRect rect;
    Player player;
};

#endif
