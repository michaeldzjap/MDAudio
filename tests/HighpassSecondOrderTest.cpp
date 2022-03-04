#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "HighpassSecondOrder.hpp"

using Catch::Approx;
using md_audio::HighpassSecondOrder;

TEST_CASE("second order highpass can filter a signal", "[HighpassSecondOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    HighpassSecondOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("a cutoff frequency of half the sample rate blocks the original signal completely") {
        HighpassSecondOrder highpass(SAMPLE_RATE / 2);

        REQUIRE(highpass.process(1.) == Approx(0.).margin(1e-9));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(highpass.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("a cutoff frequency of zero Hz passes through the original signal") {
        HighpassSecondOrder highpass(0.);

        REQUIRE(highpass.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(highpass.process(0.) == 0.);
    }
    SECTION("the integral of the impulse response is approximately equal to zero") {
        HighpassSecondOrder highpass(SAMPLE_RATE / 4, .1);

        auto sum = highpass.process(1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            sum += highpass.process(0.);

        REQUIRE(sum == Approx(0.).margin(1e-9));
    }
}
