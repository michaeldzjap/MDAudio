#include <catch2/catch_test_macros.hpp>
#include "Unit.hpp"

using md_audio::Unit;

TEST_CASE("units can be used to set and get the global sample rate", "[Unit]") {
    SECTION("getting the sample rate without setting it returns the default sample rate") {
        REQUIRE(Unit::get_sample_rate() == 44100.);
    }
    SECTION("setting the sample rate updates it") {
        Unit::set_sample_rate(48000.);

        REQUIRE(Unit::get_sample_rate() == 48000.);
        REQUIRE(Unit::get_sample_duration() == 1. / 48000.);
    }
}
