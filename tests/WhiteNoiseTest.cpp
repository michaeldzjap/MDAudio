#include <catch2/catch_test_macros.hpp>
#include "WhiteNoise.hpp"

using md_audio::WhiteNoise;

TEST_CASE("white noise generates random numbers between negative and positive one", "[WhiteNoise]") {
    constexpr auto SAMPLE_RATE = 4410;

    WhiteNoise generator;

    for (auto i = 0; i < SAMPLE_RATE; i++) {
        auto result = generator.process();

        REQUIRE((result >= -1. && result <= 1.));
    }
}
