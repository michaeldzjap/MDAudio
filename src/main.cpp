#include "AllpassCubic.hpp"
#include "Bandpass.hpp"
#include "DelayCubic.hpp"
#include "DelayStatic.hpp"
#include "HannOscillator.hpp"
#include "HighpassFirstOrder.hpp"
#include "HighpassSecondOrder.hpp"
#include "HighshelfFirstOrder.hpp"
#include "HighshelfSecondOrder.hpp"
#include "LowpassFirstOrder.hpp"
#include "LowpassSecondOrder.hpp"
#include "LowshelfFirstOrder.hpp"
#include "LowshelfSecondOrder.hpp"
#include "PitchShifter.hpp"
#include "ReverseDelay.hpp"
#include "SineOscillator.hpp"
#include "TapDelayCubic.hpp"
#include "TapDelayLinear.hpp"
#include "TapDelayStatic.hpp"
#include "TiltFirstOrder.hpp"
#include "TiltSecondOrder.hpp"
#include "VariableDelay.hpp"
#include "WhiteNoise.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "tables.hpp"
#include "utility.hpp"
#include <iomanip>
#include <iostream>

using md_audio::AllpassCubic;
using md_audio::Bandpass;
using md_audio::DelayCubic;
using md_audio::DelayStatic;
using md_audio::HannOscillator;
using md_audio::HighpassFirstOrder;
using md_audio::HighpassSecondOrder;
using md_audio::HighshelfFirstOrder;
using md_audio::HighshelfSecondOrder;
using md_audio::LowpassFirstOrder;
using md_audio::LowpassSecondOrder;
using md_audio::LowshelfFirstOrder;
using md_audio::LowshelfSecondOrder;
using md_audio::PitchShifter;
using md_audio::ReverseDelay;
using md_audio::SineOscillator;
using md_audio::TapDelayCubic;
using md_audio::TapDelayLinear;
using md_audio::TapDelayStatic;
using md_audio::TiltFirstOrder;
using md_audio::TiltSecondOrder;
using md_audio::VariableDelay;
using md_audio::WhiteNoise;
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
    constexpr auto TAPS = 3;
    constexpr auto MAX_DELAY_TIME = 5.;
    constexpr auto POOL_SIZE = next_power_of_two(
        static_cast<std::uint32_t>(SAMPLE_RATE * MAX_DELAY_TIME * sizeof(double))
    );

    Pool<POOL_SIZE> pool;
    Allocator<Pool<POOL_SIZE>> allocator(&pool);

    DelayStatic<Allocator<Pool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    HighpassFirstOrder::set_sample_rate(SAMPLE_RATE);
    HighpassSecondOrder::set_sample_rate(SAMPLE_RATE);
    HighshelfFirstOrder::set_sample_rate(SAMPLE_RATE);
    HighshelfSecondOrder::set_sample_rate(SAMPLE_RATE);
    LowpassFirstOrder::set_sample_rate(SAMPLE_RATE);
    LowpassSecondOrder::set_sample_rate(SAMPLE_RATE);
    LowshelfFirstOrder::set_sample_rate(SAMPLE_RATE);
    LowshelfSecondOrder::set_sample_rate(SAMPLE_RATE);
    TapDelayStatic<Allocator<Pool<POOL_SIZE>>, TAPS>::set_sample_rate(SAMPLE_RATE);
    TapDelayLinear<Allocator<Pool<POOL_SIZE>>, TAPS>::set_sample_rate(SAMPLE_RATE);
    TapDelayCubic<Allocator<Pool<POOL_SIZE>>, TAPS>::set_sample_rate(SAMPLE_RATE);
    TiltFirstOrder::set_sample_rate(SAMPLE_RATE);
    TiltSecondOrder::set_sample_rate(SAMPLE_RATE);
    Bandpass::set_sample_rate(SAMPLE_RATE);
    // HighpassFirstOrder highpass(0.);
    // HighpassSecondOrder highpass(11025., .1);
    // HighshelfFirstOrder highshelf(0., -6.);
    // HighshelfSecondOrder highshelf(11025., .1, -6.);
    // LowpassFirstOrder lowpass(22050.);
    // LowpassSecondOrder lowpass(11025., .1);
    // LowshelfFirstOrder lowshelf(0., -6.);
    // LowshelfSecondOrder lowshelf(11025., .1, 6.);
    // std::array<double, TAPS> delay_times = { .001, .005, .01 };
    // TapDelayStatic<Allocator<Pool<POOL_SIZE>>, TAPS> delay(allocator, MAX_DELAY_TIME, delay_times);
    // TapDelayLinear<Allocator<Pool<POOL_SIZE>>, TAPS> delay(allocator, MAX_DELAY_TIME, delay_times);
    // TapDelayCubic<Allocator<Pool<POOL_SIZE>>, TAPS> delay(allocator, MAX_DELAY_TIME, delay_times);
    // DelayStatic<Allocator<Pool<POOL_SIZE>>> delay(allocator, MAX_DELAY_TIME, .005);
    // delay.initialise();
    // TiltFirstOrder tilt(22050., -6.);
    // Bandpass bandpass(11025., 10.);
    WhiteNoise generator;

    // HannOscillator::set_sample_rate(SAMPLE_RATE);
    // HannOscillator osc(2. * SAMPLE_RATE / TABLE_SIZE);

    // SineOscillator::set_sample_rate(SAMPLE_RATE);
    // SineOscillator osc(2. * SAMPLE_RATE / TABLE_SIZE);

    // PitchShifter<Allocator<Pool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    // PitchShifter<Allocator<Pool<POOL_SIZE>>> shifter(allocator, MAX_DELAY_TIME, .01);
    // shifter.initialise();

    // ReverseDelay<Allocator<Pool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    // ReverseDelay<Allocator<Pool<POOL_SIZE>>> delay(allocator, MAX_DELAY_TIME, .01);
    // delay.initialise();

    VariableDelay<Allocator<Pool<POOL_SIZE>>>::set_sample_rate(SAMPLE_RATE);
    VariableDelay<Allocator<Pool<POOL_SIZE>>> delay(allocator, MAX_DELAY_TIME, .01, .02);
    delay.initialise();

    // for (std::size_t i = 0; i < TABLE_SIZE / 2 + 1; ++i)
    //     // std::cout << i << "\t" << osc.process() << std::endl;
    //     // std::cout << i << "\t" << hann_period(i) << std::endl;
    //     std::cout << osc.process() << ", ";

    // std::cout << std::endl;

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

    for (auto i = 0; i < 4410; i++) {
        // std::cout << i << "\t" << lowpass.process(i == 0 ? 1. : 0.) << std::endl;
        // std::cout << lowpass.process(i == 0 ? 1. : 0.) << ",";
        // std::cout << highpass.process(i == 0 ? 1. : 0.) << ",";
        // std::cout << lowshelf.process(i == 0 ? 1. : 0. /* generator.process() */) << ",";
        // std::cout << highshelf.process(i == 0 ? 1. : 0.) << ",";
        // auto out = delay.process(generator.process());
        // auto out = shifter.process(generator.process());
        // auto out = bandpass.process(generator.process());
        auto out = delay.process(generator.process());
        std::cout << i << '\t' << out << std::endl;
        // std::cout << i << '\t' << out[0] << '\t' << out[1] << '\t' << out[2] << std::endl;
        // std::cout << generator.process() << std::endl;
        // std::cout << tilt.process(i == 0 ? 1. : 0. /* generator.process() */) << ",";
    }

    // std::cout << std::endl;

    return 0;
}
