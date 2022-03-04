#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "HighshelfSecondOrder.hpp"

using Catch::Approx;
using md_audio::HighshelfSecondOrder;

TEST_CASE("second order highshelf can filter a signal", "[HighshelfSecondOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    HighshelfSecondOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("zero dB gain passes through the original signal at any cutoff frequency") {
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        HighshelfSecondOrder highshelf(cutoff, .1);

        REQUIRE(highshelf.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++) {
            REQUIRE(highshelf.process(0.) == 0.);

            highshelf.set_frequency(cutoff += increment);
        }
    }
    SECTION("six dB positive gain at a cutoff frequency of zero Hz fourfolds the amplitude of the original signal") {
        HighshelfSecondOrder highshelf(0., 1., 6.);

        REQUIRE(highshelf.process(1.) == Approx(4.).margin(1e-1));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(highshelf.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("six dB negative gain at a cutoff frequency of zero Hz quarters the amplitude of the original signal") {
        HighshelfSecondOrder highshelf(0., 1., -6.);

        REQUIRE(highshelf.process(1.) == Approx(.25).margin(1e-2));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(highshelf.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("the integral of the impulse response is approximately equal to unity at six db positive gain") {
        HighshelfSecondOrder highshelf(SAMPLE_RATE / 4, .1, 6.);

        auto sum = highshelf.process(1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            sum += highshelf.process(0.);

        REQUIRE(sum == Approx(1.).margin(1e-9));
    }
    SECTION("the integral of the impulse response is approximately equal to unity at six db negative gain") {
        HighshelfSecondOrder highshelf(SAMPLE_RATE / 4, .1, -6.);

        auto sum = highshelf.process(1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            sum += highshelf.process(0.);

        REQUIRE(sum == Approx(1.).margin(1e-9));
    }
}
