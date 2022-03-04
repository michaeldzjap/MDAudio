#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "LowpassSecondOrder.hpp"

using Catch::Approx;
using md_audio::LowpassSecondOrder;

TEST_CASE("second order lowpass can filter a signal", "[LowpassSecondOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    LowpassSecondOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("a cutoff frequency of half the sample rate passes through the original signal") {
        LowpassSecondOrder lowpass(SAMPLE_RATE / 2);

        REQUIRE(lowpass.process(1.) == Approx(1.).margin(1e-9));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowpass.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("a cutoff frequency of zero Hz blocks the original signal completely") {
        LowpassSecondOrder lowpass(0.);

        REQUIRE(lowpass.process(1.) == 0.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowpass.process(0.) == 0.);
    }
    SECTION("the integral of the impulse response is approximately equal to unity") {
        LowpassSecondOrder lowpass(SAMPLE_RATE / 4, .1);

        auto sum = lowpass.process(1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            sum += lowpass.process(0.);

        REQUIRE(sum == Approx(1.).margin(1e-9));
    }
}
