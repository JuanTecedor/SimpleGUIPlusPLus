#include "../../../src/eng/math/Vector2.hpp"
#include "../../../src/eng/math/Vector2format.hpp"

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

TEST_CASE("Vector perpendicular")
{
    const int vec_x = 2;
    const int vec_y = -1;
    Vector2i vector{vec_x, vec_y};
    Vector2i result = vector.perpendicular();
    REQUIRE(result.x == -vec_y);
    REQUIRE(result.y == vec_x);
}

TEST_CASE("Vector dot")
{
    const int vec_a_x = 5;
    Vector2i vec_a{vec_a_x, 1};
    Vector2i vec_b{-1 ,0};
    REQUIRE(vec_a.dot(vec_b) == -5);
    REQUIRE(vec_a.dot(vec_b) == vec_b.dot(vec_a));
}

TEST_CASE("Vector normalized")
{
    const int vec_x = 123;
    Vector2i vector{vec_x, 0};
    auto normalized = vector.normalized();
    REQUIRE(normalized == Vector2i::UNIT_X);
    vector.normalize();
    REQUIRE(vector == normalized);
}

TEST_CASE("Vector angle_to")
{
    // TODO
}

TEST_CASE("Vector angle")
{
    // TODO
}

TEST_CASE("Vector projected_onto")
{
    // TODO
}

TEST_CASE("Vector rotated_by")
{
    // TODO
}

TEST_CASE("Vector comp_wise_mul")
{
    // TODO
}

TEST_CASE("Vector comp_wise_div")
{
    // TODO
}

TEST_CASE("Vector comparison")
{
    Vector2i vector{1, 2};
    REQUIRE(vector != Vector2i{1, 0});
    REQUIRE(vector != Vector2i{0, 2});
    REQUIRE(vector != Vector2i{0, 0});
    REQUIRE(vector == Vector2i{1, 2});

    // TODO consider adding <, >, <=, >=
}

TEST_CASE("Vector operator+")
{
    Vector2i vec_a{-1, 2};
    Vector2i vec_b{1, 3};
    REQUIRE(vec_a + vec_b == Vector2i{0, 5});
    vec_a += vec_b;
    REQUIRE(vec_a == Vector2i{0, 5});
}

TEST_CASE("Vector operator-")
{
    Vector2i vec_a{-1, 2};
    Vector2i vec_b{1, 3};

    REQUIRE(-vec_a == Vector2i{1, -2});

    REQUIRE(vec_a - vec_b == Vector2i{-2, -1});
    REQUIRE(vec_a - vec_b != vec_b - vec_a);
    vec_a -= vec_b;
    REQUIRE(vec_a == Vector2i{-2, -1});
}

TEST_CASE("Vector operator*")
{
    Vector2i vec_a{-1, 2};
    Vector2i vec_b{2, 3};
    REQUIRE(vec_a * -2 == Vector2i{2, -4});
    REQUIRE(-2 * vec_a == vec_a * -2);
    REQUIRE(vec_a * vec_b == vec_a.dot(vec_b));
    REQUIRE(vec_a * vec_b == vec_b * vec_a);

    Vector2i vec_c{-1, 2};
    const float scalar = -2.0F;
    vec_c *= scalar;
    REQUIRE(vec_c == Vector2i{2, -4});
}

TEST_CASE("Vector operator/")
{
    const float vec_x = -1.0F;
    const float vec_y = 3.0F;
    const float div = 2.0F;
    Vector2f vec_a{vec_x, vec_y};
    Vector2f expected = {vec_x / div, vec_y / div};
    REQUIRE(vec_a / div == expected);
    vec_a /= div;
    REQUIRE(vec_a == expected);
}
