#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "TiltSecondOrder.hpp"

using Catch::Approx;
using md_audio::TiltSecondOrder;

TEST_CASE("second order tilt can filter a signal", "[TiltSecondOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    TiltSecondOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("zero dB gain passes through the original signal at any cutoff frequency") {
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        TiltSecondOrder tilt(cutoff, .1);

        REQUIRE(tilt.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++) {
            REQUIRE(tilt.process(0.) == 0.);

            tilt.set_frequency(cutoff += increment);
        }
    }
}
