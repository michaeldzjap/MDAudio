#include <cmath>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "HighshelfFirstOrder.hpp"
#include "WhiteNoise.hpp"

using Catch::Approx;
using md_audio::HighshelfFirstOrder;
using md_audio::WhiteNoise;

TEST_CASE("first order highshelf can filter a signal", "[HighshelfFirstOrder]") {
    constexpr auto SAMPLE_RATE = 4410;

    HighshelfFirstOrder::set_sample_rate(SAMPLE_RATE);

    SECTION("zero dB gain passes through the original signal at any cutoff frequency") {
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        HighshelfFirstOrder highshelf(cutoff);

        REQUIRE(highshelf.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++) {
            REQUIRE(highshelf.process(0.) == 0.);

            highshelf.set_frequency(cutoff += increment);
        }
    }
    SECTION("six dB positive gain at a cutoff frequency of zero Hz doubles the amplitude of the original signal") {
        HighshelfFirstOrder highshelf(0., 6.);

        REQUIRE(highshelf.process(1.) == Approx(2.).margin(1e-2));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(highshelf.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("six dB negative gain at a cutoff frequency of zero Hz halves the amplitude of the original signal") {
        HighshelfFirstOrder highshelf(0., -6);

        REQUIRE(highshelf.process(1.) == Approx(.5).margin(1e-2));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(highshelf.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("a cutoff frequency sweep produces a stable signal") {
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        HighshelfFirstOrder highshelf(cutoff, 6);
        WhiteNoise generator;

        for (std::size_t i = 0; i < SAMPLE_RATE; i++) {
            REQUIRE(std::abs(highshelf.process(generator.process())) <= 2.);

            highshelf.set_frequency(cutoff += increment);
        }
    }
}
