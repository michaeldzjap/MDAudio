#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "AllpassCubic.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "utility.hpp"

using Catch::Approx;
using md_audio::AllpassCubic;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;
using md_audio::utility::next_power_of_two;

TEST_CASE("cubicly interpolated allpass delays can delay the signal by a given amount of time", "[AllpassCubic]") {
    constexpr auto SAMPLE_RATE = 44100;
    constexpr auto MAX_DELAY_TIME = 1.;
    constexpr auto POOL_SIZE = next_power_of_two(
        static_cast<std::uint32_t>(SAMPLE_RATE * MAX_DELAY_TIME * sizeof(double))
    );

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<double, StaticPool<POOL_SIZE>> allocator(&pool);

    auto delay_time = .001;
    auto gain = 0.;
    AllpassCubic<StaticAllocator<double, StaticPool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    AllpassCubic<StaticAllocator<double, StaticPool<POOL_SIZE>>> allpass(allocator, MAX_DELAY_TIME, delay_time, gain);

    REQUIRE(allpass.initialise());

    SECTION("zero gain reduces cubicly interpolated allpass delay to simple cubicly interpolated delay") {
        for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time) - 1; i++)
            REQUIRE(allpass.process(1.) == 0.);

        REQUIRE(allpass.process(1.) == Approx(-.0405));
        REQUIRE(allpass.process(1.) == Approx(.936));

        delay_time /= 2;
        allpass.set_delay_time(delay_time);

        for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time) - 1; i++)
            REQUIRE(allpass.process(.5) == 1.);

        REQUIRE(allpass.process(.5) == Approx(1.01128125));
        REQUIRE(allpass.process(.5) == Approx(.5143125));
        REQUIRE(allpass.process(.5) == Approx(.49940625));
        REQUIRE(allpass.process(.5) == .5);
    }
    SECTION("half a unit of gain creates feedback") {
        allpass.set_gain(.5);

        for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time) - 1; i++)
            REQUIRE(allpass.process(1.) == -.5);

        REQUIRE(allpass.process(1.) == Approx(-.530375));
        REQUIRE(allpass.process(1.) == Approx(.202));

        delay_time /= 2;
        allpass.set_delay_time(delay_time);

        for (auto i = 0; i < static_cast<std::uint32_t>(SAMPLE_RATE * delay_time) - 3; i++)
            REQUIRE(allpass.process(.5) == .5);

        REQUIRE(allpass.process(.5) == Approx(.500342668));
        REQUIRE(allpass.process(.5) == Approx(.476985137));
        REQUIRE(allpass.process(.5) == Approx(.848419285));
        REQUIRE(allpass.process(.5) == Approx(.510482223));
        REQUIRE(allpass.process(.5) == Approx(.499583188));
        REQUIRE(allpass.process(.5) == .5);
    }
}
