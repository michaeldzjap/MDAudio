#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "LowshelfSecondOrder.hpp"

using Catch::Approx;
using md_audio::LowshelfSecondOrder;

TEST_CASE("second order lowshelf can filter a signal", "[LowshelfSecondOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    LowshelfSecondOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("zero dB gain passes through the original signal at any cutoff frequency") {
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        LowshelfSecondOrder lowshelf(cutoff, .1);

        REQUIRE(lowshelf.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++) {
            REQUIRE(lowshelf.process(0.) == 0.);

            lowshelf.set_frequency(cutoff += increment);
        }
    }
    SECTION("six dB positive gain at a cutoff frequency of half the sample rate fourfolds the amplitude of the original signal") {
        LowshelfSecondOrder lowshelf(SAMPLE_RATE / 2, 1., 6.);

        REQUIRE(lowshelf.process(1.) == Approx(4.).margin(1e-1));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowshelf.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("six dB negative gain at a cutoff frequency of half the sample rate quarters the amplitude of the original signal") {
        LowshelfSecondOrder lowshelf(SAMPLE_RATE / 2, 1., -6.);

        REQUIRE(lowshelf.process(1.) == Approx(.25).margin(1e-2));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowshelf.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("the integral of the impulse response is approximately equal to four at six db positive gain") {
        LowshelfSecondOrder lowshelf(SAMPLE_RATE / 4, .1, 6.);

        auto sum = lowshelf.process(1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            sum += lowshelf.process(0.);

        REQUIRE(sum == Approx(4.).margin(1e-1));
    }
    SECTION("the integral of the impulse response is approximately equal to a quarter at six db negative gain") {
        LowshelfSecondOrder lowshelf(SAMPLE_RATE / 4, .1, -6.);

        auto sum = lowshelf.process(1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            sum += lowshelf.process(0.);

        REQUIRE(sum == Approx(.25).margin(1e-2));
    }
}
