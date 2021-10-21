#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "utility.hpp"

using Catch::Approx;
using md_audio::utility::clip;
using md_audio::utility::linear_interp;
using md_audio::utility::next_power_of_two;

TEST_CASE("clipped values are computed", "[clip]") {
    REQUIRE(clip(0, 1, 2) == 1);
    REQUIRE(clip(3, 1, 2) == 2);
    REQUIRE(clip(1.5, 1.6, 1.8) == 1.6);
    REQUIRE(clip<double>(3.4, 2, 3) == 3.);
}
TEST_CASE("linear interpolated values are computed", "[linear_interp]") {
    REQUIRE(linear_interp(.0, .1, .2) == .1);
    REQUIRE(linear_interp(.5, .1, .2) == Approx(.15));
    REQUIRE(linear_interp(.5, .2, .1) == Approx(.15));
}
TEST_CASE("next powers of two are computed", "[next_power_of_two]") {
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
