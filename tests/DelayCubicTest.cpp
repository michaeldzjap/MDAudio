#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "DelayCubic.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "utility.hpp"

using Catch::Approx;
using md_audio::DelayCubic;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;
using md_audio::utility::next_power_of_two;

TEST_CASE("cubicly interpolated delays can delay the signal by a given amount of time", "[DelayCubic]") {
    constexpr auto SAMPLE_RATE = 44100;
    constexpr auto MAX_DELAY_TIME = 1.;
    constexpr auto POOL_SIZE = next_power_of_two(
        static_cast<std::uint32_t>(SAMPLE_RATE * MAX_DELAY_TIME * sizeof(double))
    );

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<double, StaticPool<POOL_SIZE>> allocator(&pool);

    auto delay_time = .001;
    DelayCubic<StaticAllocator<double, StaticPool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    DelayCubic<StaticAllocator<double, StaticPool<POOL_SIZE>>> delay(allocator, MAX_DELAY_TIME, delay_time);

    REQUIRE(delay.initialise());

    for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time) - 1; i++)
        REQUIRE(delay.process(1.) == 0.);

    REQUIRE(delay.process(1.) == Approx(-.0405));
    REQUIRE(delay.process(1.) == Approx(.936));

    delay_time /= 2;
    delay.set_delay_time(delay_time);

    for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time) - 1; i++)
        REQUIRE(delay.process(.5) == 1.);

    REQUIRE(delay.process(.5) == Approx(1.01128125));
    REQUIRE(delay.process(.5) == Approx(.5143125));
    REQUIRE(delay.process(.5) == Approx(.49940625));
    REQUIRE(delay.process(.5) == .5);
}
