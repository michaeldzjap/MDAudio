#include <cmath>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "HighpassFirstOrder.hpp"
#include "WhiteNoise.hpp"

using Catch::Approx;
using md_audio::HighpassFirstOrder;
using md_audio::WhiteNoise;

TEST_CASE("first order highpass can filter a signal", "[HighpassFirstOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    HighpassFirstOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("a cutoff frequency of half the sample rate blocks the original signal completely") {
        HighpassFirstOrder highpass(SAMPLE_RATE / 2);

        REQUIRE(highpass.process(1.) == Approx(0.).margin(1e-9));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(highpass.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("a cutoff frequency of zero Hz passes through the original signal") {
        HighpassFirstOrder highpass(0.);

        REQUIRE(highpass.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(highpass.process(0.) == 0.);
    }
    SECTION("a cutoff frequencsy sweep produces a stable signal") {
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        HighpassFirstOrder highpass(cutoff);
        WhiteNoise generator;

        for (std::size_t i = 0; i < SAMPLE_RATE; i++) {
            REQUIRE(std::abs(highpass.process(generator.process())) <= 1.);

            highpass.set_frequency(cutoff += increment);
        }
    }
}
