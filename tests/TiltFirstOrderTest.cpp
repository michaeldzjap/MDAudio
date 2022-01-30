#include <cmath>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "TiltFirstOrder.hpp"
#include "WhiteNoise.hpp"

using Catch::Approx;
using md_audio::TiltFirstOrder;
using md_audio::WhiteNoise;

TEST_CASE("first order tilt can filter a signal", "[TiltFirstOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    TiltFirstOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("zero dB gain passes through the original signal at any cutoff frequency") {
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        TiltFirstOrder tilt(cutoff);

        REQUIRE(tilt.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++) {
            REQUIRE(tilt.process(0.) == 0.);

            tilt.set_frequency(cutoff += increment);
        }
    }
}
