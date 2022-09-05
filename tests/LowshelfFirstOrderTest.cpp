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
        auto cutoff = 0.;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        LowshelfFirstOrder lowshelf(cutoff);

        REQUIRE(lowshelf.process(1.) == 1.);

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++) {
            REQUIRE(lowshelf.process(0.) == 0.);

            lowshelf.set_frequency(cutoff += increment);
        }
    }
    SECTION("six dB positive gain at a cutoff frequency of half the sample rate doubles the amplitude of the original signal") {
        LowshelfFirstOrder lowshelf(SAMPLE_RATE / 2, 6.);

        REQUIRE(lowshelf.process(1.) == Approx(2.).margin(1e-2));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowshelf.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("six dB negative gain at a cutoff frequency of half the sample rate halves the amplitude of the original signal") {
        LowshelfFirstOrder lowshelf(SAMPLE_RATE / 2, -6.);

        REQUIRE(lowshelf.process(1.) == Approx(.5).margin(1e-2));

        for (std::size_t i = 0; i < SAMPLE_RATE / 10; i++)
            REQUIRE(lowshelf.process(0.) == Approx(0.).margin(1e-9));
    }
    SECTION("a cutoff frequency sweep produces a stable signal") {
        auto cutoff = SAMPLE_RATE / 2;
        auto increment = (SAMPLE_RATE / 2) / SAMPLE_RATE;

        LowshelfFirstOrder lowshelf(cutoff, 6.);
        WhiteNoise generator;

        for (std::size_t i = 0; i < SAMPLE_RATE; i++) {
            REQUIRE(std::abs(lowshelf.process(generator.process())) <= 2.);

            lowshelf.set_frequency(cutoff -= increment);
        }
    }
}
