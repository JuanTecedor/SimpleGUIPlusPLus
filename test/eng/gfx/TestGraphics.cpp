#include "../../../src/eng/System.hpp"
#include "../../../src/eng/gfx/Graphics.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("WORLD_TO_SCREEN_B2B")
{
    using Catch::Matchers::WithinRel;

    const float start_x = 25.5F;
    const float start_y = 16.5F;
    System system{};
    auto graphics = Graphics{"", {}};
    auto pos = PositionF{start_x, start_y};
    auto screen = graphics.world_to_screen(pos);
    auto world = graphics.screen_to_world(screen);
    REQUIRE(pos == world);
}
