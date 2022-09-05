#include <catch2/catch_test_macros.hpp>
#include "Latch.hpp"

using md_audio::Latch;

TEST_CASE("latch sample and holds first signal based on zero crossings of second signal", "[Latch]") {
    constexpr auto SAMPLE_RATE = 4410;

    Latch latch;

    REQUIRE(latch.process(1., .0) == 1.);
    REQUIRE(latch.process(1., .5) == 1.);
    REQUIRE(latch.process(0., 1.) == 1.);
    REQUIRE(latch.process(0., 0.) == 0.);
}
