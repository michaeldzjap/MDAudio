#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "LowpassFirstOrder.hpp"
#include "WhiteNoise.hpp"

using Catch::Approx;
using md_audio::LowpassFirstOrder;
using md_audio::WhiteNoise;

TEST_CASE("first order lowpass can filter a signal", "[LowpassFirstOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    LowpassFirstOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("a cutoff frequency of half the sample rate passes through the original signal") {
        LowpassFirstOrder lowpass(SAMPLE_RATE / 2);

        REQUIRE(lowpass.process(1.) == Approx(1.).margin(1e-9));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowpass.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("a cutoff frequency of zero Hz blocks the original signal completely") {
        LowpassFirstOrder lowpass(0.);

        REQUIRE(lowpass.process(1.) == 0.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowpass.process(0.) == 0.);
    }
    SECTION("a cutoff frequencsy sweep produces a stable signal") {
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        LowpassFirstOrder lowpass(cutoff);
        WhiteNoise generator;

        for (std::size_t i = 0; i < SAMPLE_RATE; i++) {
            REQUIRE(std::abs(lowpass.process(generator.process())) <= 1.);

            lowpass.set_frequency(cutoff += increment);
        }
    }
}
