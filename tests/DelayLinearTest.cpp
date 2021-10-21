#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "DelayLinear.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "types.hpp"
#include "utility.hpp"

using Catch::Approx;
using md_audio::DelayLinear;
using md_audio::MdFloat;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;
using md_audio::utility::next_power_of_two;

TEST_CASE("linearly interpolated delays can delay the signal by a given amount of time", "[DelayLinear]") {
    constexpr auto SAMPLE_RATE = 44100;
    constexpr auto MAX_DELAY_TIME = 1.;
    constexpr auto POOL_SIZE = next_power_of_two(
        static_cast<std::uint32_t>(SAMPLE_RATE * MAX_DELAY_TIME * sizeof(MdFloat))
    );

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<MdFloat, StaticPool<POOL_SIZE>> allocator(&pool);

    auto delay_time = .001;
    DelayLinear<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    DelayLinear<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>> delay(allocator, MAX_DELAY_TIME, delay_time);

    REQUIRE(delay.initialise());

    for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time); i++)
        REQUIRE(delay.process(1.) == 0.);

    REQUIRE(delay.process(1.) == Approx(.9)); // a + x(b - a) = 1 + 0.1(0 - 1)

    delay_time /= 2;
    delay.set_delay_time(delay_time);

    for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time); i++)
        REQUIRE(delay.process(.5) == 1.);

    REQUIRE(delay.process(.5) == Approx(.525)); // a + x(b - a) = 0.5 + 0.05(1 - 0.5)
    REQUIRE(delay.process(.5) == .5);
}
