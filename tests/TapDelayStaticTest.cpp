#include <array>
#include <catch2/catch_test_macros.hpp>
#include "TapDelayStatic.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "utility.hpp"

using md_audio::TapDelayStatic;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;
using md_audio::utility::next_power_of_two;

TEST_CASE("uninterpolated tap delays can delay the signal by a given amount of time", "[TapDelayStatic]") {
    constexpr auto SAMPLE_RATE = 44100;
    constexpr auto MAX_DELAY_TIME = 1.;
    constexpr auto POOL_SIZE = next_power_of_two(
        static_cast<std::uint32_t>(SAMPLE_RATE * MAX_DELAY_TIME * sizeof(double))
    );
    constexpr auto TAPS = 1;

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<double, StaticPool<POOL_SIZE>> allocator(&pool);

    std::array<double, TAPS> delay_time = { .001 };
    TapDelayStatic<StaticAllocator<double, StaticPool<POOL_SIZE>>, TAPS>::set_sample_rate(SAMPLE_RATE);
    TapDelayStatic<StaticAllocator<double, StaticPool<POOL_SIZE>>, TAPS> delay(allocator, MAX_DELAY_TIME, delay_time);

    REQUIRE(delay.initialise());

    for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time[0]); i++)
        REQUIRE(delay.process(1.)[0] == 0.);

    REQUIRE(delay.process(1.)[0] == 1.);

    delay_time[0] /= 2;
    delay.set_delay_time(delay_time);

    for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time[0]); i++)
        REQUIRE(delay.process(.5)[0] == 1.);

    REQUIRE(delay.process(.5)[0] == .5);
}
