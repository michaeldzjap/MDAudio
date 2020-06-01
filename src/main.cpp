#include "Delay.hpp"
#include "HannOscillator.hpp"
#include "InterpolationType.hpp"
#include "Normaliser.hpp"
#include "Phasor.hpp"
#include "Reverb.hpp"
#include "ReverbConfig.hpp"
#include "ReverseDelay.hpp"
#include "ReversibleDelay.hpp"
#include "StaticPool.hpp"
#include "TapDelay.hpp"
#include "TapDelayCubic.hpp"
#include "TapDelayLinear.hpp"
#include "TapDelayStatic.hpp"
#include "WhiteNoise.hpp"
#include "types.hpp"
#include <iomanip>
#include <iostream>

template <std::size_t Size>
using Pool = md_audio::memory::StaticPool<Size>;

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(4);

    // Delay
    constexpr auto MAX_DELAY = 102;
    constexpr auto MAX_DELAY_SIZE = MAX_DELAY * sizeof(md_audio::MdFloat);

    Pool<MAX_DELAY_SIZE> pool;

    // // Tap delay
    // constexpr auto MAX_DELAY = 102;
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY * sizeof(md_audio::MdFloat);
    // constexpr auto TAPS = 4;
    // constexpr auto TAPS_SIZE = TAPS * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + TAPS_SIZE;
    // constexpr md_audio::MdFloat DELAY_TIMES[TAPS] = {99.725535, 50., 5.123, 25.56256};
    //
    // Pool<TOTAL_SIZE> pool;

    // // Normaliser
    // constexpr auto DURATION = 102;
    // constexpr auto DURATION_SIZE = DURATION * sizeof(md_audio::MdFloat) * 3;
    //
    // Pool<DURATION_SIZE> pool;

    // // ReverseDelay delay
    // constexpr auto MAX_DELAY = 102;
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = OVERLAP * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat) + sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + OVERLAP_SIZE;
    //
    // Pool<TOTAL_SIZE> pool;

    // // ReversibleDelay delay
    // constexpr auto MAX_DELAY = 102;
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = (OVERLAP + 1) * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat)) + OVERLAP * (sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + OVERLAP_SIZE;
    //
    // Pool<TOTAL_SIZE> pool;

    md_audio::Delay delay(pool, 102, 50.73536f, md_audio::InterpolationType::linear);
    // md_audio::TapDelayLinear delay(pool, 102, TAPS);
    // md_audio::TapDelay delay(pool, 102, TAPS, md_audio::InterpolationType::cubic);
    // md_audio::ReverseDelay delay(pool, MAX_DELAY, 50.f, OVERLAP);
    // md_audio::ReversibleDelay delay(pool, MAX_DELAY, 50.f, OVERLAP);
    // md_audio::Normaliser normaliser(pool, DURATION);
    md_audio::WhiteNoise noise;

    // delay.set_delay(DELAY_TIMES);

    // normaliser.initialise();

    for (std::size_t i = 0; i < 441; ++i) {
        // md_audio::MdFloat z[TAPS];

        const auto y = noise.perform();
        // const auto z = normaliser.perform(y);
        // delay.perform(y, z, TAPS);
        auto z = delay.perform(y);

        std::cout << i << "\t" << y << "\t" << z << std::endl;

        // std::cout << i << "\t";
        //
        // for (auto i = 0; i < TAPS; ++i)
        //     // std::cout << delay.read(i) << ", ";
        //     std::cout << z[i] << ", ";
        //
        // std::cout << std::endl;

        // delay.write(y);
    }
}
