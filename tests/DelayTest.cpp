#include <catch2/catch_test_macros.hpp>
#include "Delay.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "types.hpp"
#include "utility.hpp"

using md_audio::Delay;
using md_audio::MdFloat;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;
using md_audio::utility::next_power_of_two;

TEST_CASE("delays can delay the signal by a given amount of time", "[Delay]") {
    constexpr auto SAMPLE_RATE = 44100;
    constexpr auto MAX_DELAY_TIME = 1.;
    constexpr auto DELAY_TIME = .1;
    constexpr auto POOL_SIZE = next_power_of_two(
        static_cast<std::uint32_t>(SAMPLE_RATE * MAX_DELAY_TIME * sizeof(MdFloat))
    );

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<MdFloat, StaticPool<POOL_SIZE>> allocator(&pool);

    Delay<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    Delay<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>> delay(allocator, MAX_DELAY_TIME, DELAY_TIME);

    REQUIRE(delay.initialise());

    for (auto i = 0; i < SAMPLE_RATE * DELAY_TIME; i++) {
        REQUIRE(delay.process(1.) == 0.);
    }

    REQUIRE(delay.process(1.) == 1.);
}
