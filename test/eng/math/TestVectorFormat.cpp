#include "../../../src/eng/math/Vector2.hpp"
#include "../../../src/eng/math/Vector2format.hpp"
#include "../../util/OstreamRedirector.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vector format")
{
    Vector2i vec{1, -2};
    REQUIRE(to_string(vec) == "Vector2(x=1, y=-2)");
}

TEST_CASE("Vector ostream")
{
    juan::OstreamRedirector os_redir{std::cout};
    Vector2i vec{1, -2};
    std::cout << vec;
    REQUIRE(os_redir.get() == "Vector2(x=1, y=-2)");
}
