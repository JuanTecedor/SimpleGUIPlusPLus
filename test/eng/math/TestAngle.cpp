#include "../../../src/eng/math/Angle.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <numbers>

TEST_CASE("0 Angle")
{
    using Catch::Matchers::WithinRel;
    Angle angle;
    REQUIRE_THAT(angle.as_degrees(), WithinRel(0.F));
    REQUIRE_THAT(angle.as_radians(), WithinRel(0.F));
}

TEST_CASE("180 Angle")
{
    using Catch::Matchers::WithinRel;
    auto angle = Angle::from_degrees(Angle::HALF_CIRCLE_DEG);
    REQUIRE_THAT(angle.as_degrees(), WithinRel(Angle::HALF_CIRCLE_DEG));
    REQUIRE_THAT(angle.as_radians(), WithinRel(std::numbers::pi_v<float>));
}

TEST_CASE("Radian")
{
    using Catch::Matchers::WithinRel;
    auto angle1 = Angle::from_degrees(Angle::THREE_QUARTER_CIRCLE_DEG);
    auto angle2 = Angle::from_radians(Angle::ONE_POINT_FIVE_PI);
    REQUIRE_THAT(angle1.as_radians(), WithinRel(angle2.as_radians()));
    REQUIRE_THAT(angle1.as_degrees(), WithinRel(angle2.as_degrees()));
}

TEST_CASE("Angle Sum")
{
    using Catch::Matchers::WithinRel;
    auto angle1 = Angle::from_degrees(Angle::HALF_CIRCLE_DEG);
    auto angle2 = Angle::from_degrees(Angle::HALF_CIRCLE_DEG);
    angle1 += angle2;
    REQUIRE_THAT(angle1.as_degrees(), WithinRel(0.F));
}
