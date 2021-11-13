#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "AllpassLinear.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "utility.hpp"

using Catch::Approx;
using md_audio::AllpassLinear;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;
using md_audio::utility::next_power_of_two;

TEST_CASE("linearly interpolated allpass delays can delay the signal by a given amount of time", "[AllpassLinear]") {
    constexpr auto SAMPLE_RATE = 44100;
    constexpr auto MAX_DELAY_TIME = 1.;
    constexpr auto POOL_SIZE = next_power_of_two(
        static_cast<std::uint32_t>(SAMPLE_RATE * MAX_DELAY_TIME * sizeof(double))
    );

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<double, StaticPool<POOL_SIZE>> allocator(&pool);

    auto delay_time = .001;
    auto gain = 0.;
    AllpassLinear<StaticAllocator<double, StaticPool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    AllpassLinear<StaticAllocator<double, StaticPool<POOL_SIZE>>> allpass(allocator, MAX_DELAY_TIME, delay_time, gain);

    REQUIRE(allpass.initialise());

    SECTION("zero gain reduces linearly interpolated allpass delay to simple linearly interpolated delay") {
        for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time); i++)
            REQUIRE(allpass.process(1.) == 0.);

        REQUIRE(allpass.process(1.) == Approx(.9));

        delay_time /= 2;
        allpass.set_delay_time(delay_time);

        for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time); i++)
            REQUIRE(allpass.process(.5) == 1.);

        REQUIRE(allpass.process(.5) == Approx(.525));
        REQUIRE(allpass.process(.5) == .5);
    }
    SECTION("half a unit of gain creates feedback") {
        allpass.set_gain(.5);

        for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time); i++)
            REQUIRE(allpass.process(1.) == -.5);

        REQUIRE(allpass.process(1.) == Approx(.175));

        delay_time /= 2;
        allpass.set_delay_time(delay_time);

        for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time) - 1; i++)
            REQUIRE(allpass.process(.5) == .5);

        REQUIRE(allpass.process(.5) == Approx(.820625));
        REQUIRE(allpass.process(.5) == Approx(.516875));
        REQUIRE(allpass.process(.5) == .5);
    }
}
