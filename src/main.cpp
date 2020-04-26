#include "AllpassStatic.hpp"
#include "Buffer.hpp"
#include "DelayStatic.hpp"
#include "DelayCubic.hpp"
#include "DelayLinear.hpp"
#include "HighpassFirstOrder.hpp"
#include "HighshelfFirstOrder.hpp"
#include "Latch.hpp"
#include "LowpassFirstOrder.hpp"
#include "TapDelay.hpp"
#include "TapDelayCubic.hpp"
#include "TapDelayLinear.hpp"
#include "Phasor.hpp"
#include "PitchShifter.hpp"
#include "Reverb.hpp"
#include "ReverbConfig.hpp"
#include "ReverseDelay.hpp"
#include "ReversibleDelay.hpp"
#include "SineOscillator.hpp"
#include "SineShaper.hpp"
#include "StaticAllocator.hpp"
#include "StaticPool.hpp"
#include "WhiteNoise.hpp"
#include "tables.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <array>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <limits>
#include <typeinfo>

template <std::size_t Size>
using Pool = md_audio::memory::StaticPool<Size * sizeof(md_audio::MdFloat)>;

template <typename Pool>
using Allocator = md_audio::memory::StaticAllocator<md_audio::MdFloat, Pool>;

int main() {
    // std::cout.precision(std::numeric_limits<md_audio::MdFloat>::max_digits10);
    std::cout << std::fixed;
    std::cout << std::setprecision(4);

    // for (std::size_t i = 0; i < md_audio::table_size + 1; i++)
    //     std::cout << i << "\t" << md_audio::sine_table[i] << ", " << typeid(md_audio::sine_table[i]).name() << std::endl;

    constexpr auto size = 102;
    // constexpr auto size = md_audio::ReverbConfig::total_size;
    // constexpr auto size = md_audio::ReverbConfig::total_size + 102;

    Pool<size> pool;
    Allocator<Pool<size>> allocator(&pool);

    // md_audio::Reverb<Allocator<Pool<size>>> reverb(allocator);
    // reverb.initialise();
    // reverb.set_size(1.f);
    // reverb.set_pre_delay(.5f);
    // reverb.set_mix(1.f);
    // md_audio::AllpassStatic<100> allpass(50.354261f, .1f);
    // md_audio::DelayStatic delay(allocator, 100.f, 50.354261f);
    // md_audio::DelayLinear delay(allocator, 101.f, 50.354261f);
    // md_audio::DelayCubic delay(allocator, 102.f, 50.354261f);
    constexpr auto TAPS = 4;
    constexpr std::array<md_audio::MdFloat, TAPS> delay_times{99.725535f, 50.f, 5.123f, 25.56256f};

    // md_audio::TapDelay<TAPS> delay(allocator, 102.f, delay_times);
    md_audio::TapDelay<TAPS> delay(allocator, 102.f);
    // md_audio::TapDelayLinear<TAPS> delay(allocator, 102.f);
    // md_audio::TapDelayCubic<TAPS> delay(allocator, 102.f);
    delay.initialise();
    delay.set_delay(delay_times);
    // constexpr auto length = static_cast<std::uint32_t>(md_audio::utility::seconds_to_samples(.5f)) + 1;
    // md_audio::ReverseDelay<2> reverser(allocator, 102.f, 80.123f);
    // md_audio::ReversibleDelay<2> reverser(allocator, 102.f, 80.123f);
    // reverser.initialise();
    // reverser.toggle_reverse();
    // constexpr auto length = static_cast<std::uint32_t>(md_audio::utility::seconds_to_samples(.12f)) + 1;
    // md_audio::PitchShifter<length, 2> shifter(12.f, md_audio::utility::seconds_to_samples(.12f));
    // md_audio::HighshelfFirstOrder filter(8000., 6.);
    // md_audio::Lowpass filter(100.);
    // md_audio::SineOscillator osc(44100.f / 512.f);
    // md_audio::SineShaper shaper;
    md_audio::WhiteNoise noise;
    // md_audio::Phasor phasor;
    // md_audio::Latch latch;

    // delay.set_delay(99.1234f);
    // phasor.set_frequency(44.1f);
    // phasor.set_phase(.0f);

    // std::cout << std::fixed << std::setprecision(6);

    for (std::size_t i = 0; i < 441; i++) {
        // const auto z = shaper.perform(osc.perform() * 2.);
        // const auto z = filter.perform(osc.perform());
        // const auto z = allpass.perform(osc.perform());
        const auto y = noise.perform();
        // const auto y = phasor.perform();
        // const auto z = latch.perform(noise.perform(), y);
        // const auto z = reverser.perform(noise.perform());
        // const auto z = shifter.perform(osc.perform());
        // const auto z = reverb.perform(y);
        // const auto z = delay.perform(y);

        // std::cout << i << "\t" << y << "\t" << z << std::endl;
        // std::cout << i << "\t" << z[0] << std::endl;
        // std::cout << i << "\t" << z[0] << ", " << z[1] << std::endl;

        // std::cout << i << "\t";
        //
        // for (auto i = 0; i < TAPS; i++)
        //     std::cout << z[i] << ", ";
        //
        // std::cout << std::endl;

        std::cout << i << "\t";

        for (auto i = 0; i < TAPS; i++) {
            auto z = delay.read(i);

            std::cout << z << ", ";
        }

        std::cout << std::endl;

        delay.write(y);
    }

    return 0;
}
