#include <catch2/catch_test_macros.hpp>
#include "utility.hpp"

using md_audio::utility::next_power_of_two;

TEST_CASE("next power of two is computed", "[next_power_of_two]") {
    REQUIRE(next_power_of_two(0) == 2);
    REQUIRE(next_power_of_two(1) == 2);
    REQUIRE(next_power_of_two(2) == 2);
    REQUIRE(next_power_of_two(3) == 4);
    REQUIRE(next_power_of_two(5) == 8);
    REQUIRE(next_power_of_two(9) == 16);
    REQUIRE(next_power_of_two(24) == 32);
    REQUIRE(next_power_of_two(60) == 64);
    REQUIRE(next_power_of_two(120) == 128);
    REQUIRE(next_power_of_two(129) == 256);
}
