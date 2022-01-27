#include <cmath>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "LowshelfFirstOrder.hpp"
#include "WhiteNoise.hpp"

using Catch::Approx;
using md_audio::LowshelfFirstOrder;
using md_audio::WhiteNoise;

TEST_CASE("first order lowshelf can filter a signal", "[LowshelfFirstOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    LowshelfFirstOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("zero dB gain passes through the original signal at any cutoff frequency") {
        LowshelfFirstOrder lowshelf(SAMPLE_RATE / 4, 0.);

        REQUIRE(lowshelf.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowshelf.process(0.) == 0.);
    }
}
