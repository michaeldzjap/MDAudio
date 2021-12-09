#include "AllpassCubic.hpp"
#include "DelayCubic.hpp"
#include "HannOscillator.hpp"
#include "SineOscillator.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "tables.hpp"
#include "utility.hpp"
#include <iomanip>
#include <iostream>

using md_audio::AllpassCubic;
using md_audio::DelayCubic;
using md_audio::HannOscillator;
using md_audio::SineOscillator;
using md_audio::hann_period;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;
using md_audio::sine_period;
using md_audio::utility::lookup;
using md_audio::utility::next_power_of_two;
using md_audio::TABLE_SIZE;

template <std::size_t SIZE>
using Pool = md_audio::memory::StaticPool<SIZE>;

template <typename Pool>
using Allocator = md_audio::memory::StaticAllocator<double, Pool>;

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(20);

    constexpr auto SAMPLE_RATE = 44100.;

    // HannOscillator::set_sample_rate(SAMPLE_RATE);
    // HannOscillator osc(2. * SAMPLE_RATE / TABLE_SIZE);

    SineOscillator::set_sample_rate(SAMPLE_RATE);
    SineOscillator osc(2. * SAMPLE_RATE / TABLE_SIZE);

    for (std::size_t i = 0; i < TABLE_SIZE / 2 + 1; ++i)
        // std::cout << i << "\t" << osc.process() << std::endl;
        // std::cout << i << "\t" << hann_period(i) << std::endl;
        std::cout << osc.process() << ", ";

    std::cout << std::endl;

    // constexpr auto MAX_DELAY_TIME = 1.;
    // constexpr auto POOL_SIZE = next_power_of_two(
    //     static_cast<std::uint32_t>(SAMPLE_RATE * MAX_DELAY_TIME * sizeof(double))
    // );
    //
    // Pool<POOL_SIZE> pool;
    // Allocator<Pool<POOL_SIZE>> allocator(&pool);
    //
    // auto delay_time = .001;

    // DelayCubic<Allocator<Pool<POOL_SIZE>>> delay(allocator, MAX_DELAY_TIME, delay_time);
    // AllpassCubic<Allocator<Pool<POOL_SIZE>>> allpass(allocator, MAX_DELAY_TIME, delay_time);

    // delay.initialise();
    // allpass.initialise();
    // allpass.set_gain(.5);

    // for (std::size_t i = 0; i < 44; ++i)
        // std::cout << i << "\t" << delay.process(1.) << std::endl;
        // std::cout << i << "\t" << allpass.process(1.) << std::endl;

    // std::cout << 44 << "\t" << delay.process(1.) << std::endl;
    // std::cout << 44 << "\t" << allpass.process(1.) << std::endl;

    // delay.set_delay_time(.0005);
    // allpass.set_delay_time(.0005);

    // for (std::size_t i = 0; i < 22; ++i)
        // std::cout << 45 + i << "\t" << delay.process(.5) << std::endl;
        // std::cout << 45 + i << "\t" << allpass.process(.5) << std::endl;

    // std::cout << 67 << "\t" << delay.process(.5) << std::endl;
    // std::cout << 68 << "\t" << delay.process(.5) << std::endl;
    // std::cout << 69 << "\t" << delay.process(.5) << std::endl;

    // std::cout << 67 << "\t" << allpass.process(.5) << std::endl;
    // std::cout << 68 << "\t" << allpass.process(.5) << std::endl;
    // std::cout << 69 << "\t" << allpass.process(.5) << std::endl;

    // for (std::size_t i = 0; i < TABLE_SIZE + 1; i++)
        // std::cout << i << "\t" << i / static_cast<double>(TABLE_SIZE) << std::endl;
        // std::cout << i / static_cast<double>(TABLE_SIZE) << ", ";



    return 0;
}
