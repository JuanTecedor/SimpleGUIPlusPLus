#include "../../../src/eng/math/Vector2.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Vector constructors")
{
    using Catch::Matchers::WithinRel;

    Vector2i vec1{};
    REQUIRE(vec1.x == 0);
    REQUIRE(vec1.y == 0);

    Vector2i vec2{1, -2};
    auto vec3 = vec2;
    REQUIRE(vec3.x == 1);
    REQUIRE(vec3.y == -2);

    constexpr auto modulus = 10.F;
    auto angle = Angle::from_degrees(Angle::ONE_POINT_FIVE_PI);
    auto vec_x = modulus * std::cos(angle.as_radians());
    auto vec_y = modulus * std::sin(angle.as_radians());
    Vector2f vec4{modulus, angle};
    REQUIRE_THAT(vec4.x, WithinRel(vec_x));
    REQUIRE_THAT(vec4.y, WithinRel(vec_y));
}

TEST_CASE("Vector length")
{
    using Catch::Matchers::WithinRel;
    Vector2f vector{100.0F, -1.F};
    const auto length = std::sqrt(10001.F);
    REQUIRE_THAT(vector.length(), WithinRel(length));

    const int vec_x = 10;
    const int vec_y = -5;
    Vector2i vector2{vec_x, vec_y};
    REQUIRE(vector2.length_squared() == 125);
}
