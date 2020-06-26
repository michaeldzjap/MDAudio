#include "AllpassCubic.hpp"
#include "AllpassLinear.hpp"
#include "AllpassStatic.hpp"
#include "Delay.hpp"
#include "DelayCubic.hpp"
#include "DelayLinear.hpp"
#include "DelayStatic.hpp"
#include "HannOscillator.hpp"
#include "InterpolationType.hpp"
#include "Latch.hpp"
#include "Normaliser.hpp"
#include "Phasor.hpp"
#include "PitchShifter.hpp"
#include "Reverb.hpp"
#include "ReverbConfig.hpp"
#include "ReverseDelay.hpp"
#include "ReversibleDelay.hpp"
#include "StaticPool.hpp"
#include "TapDelay.hpp"
#include "TapDelayCubic.hpp"
#include "TapDelayLinear.hpp"
#include "TapDelayStatic.hpp"
#include "VariableDelay.hpp"
#include "WhiteNoise.hpp"
#include "constants.hpp"
#include "types.hpp"
#include <iomanip>
#include <iostream>

template <std::size_t Size>
using Pool = md_audio::memory::StaticPool<Size>;

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(9);

    // Allpass / Delay Static
    constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    constexpr auto DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    constexpr auto MAX_DELAY_SAMPLES = static_cast<std::uint32_t>(MAX_DELAY_TIME * md_audio::sample_rate) + 1;
    constexpr auto TOTAL_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);

    Pool<TOTAL_SIZE> pool;

    // // Allpass / Delay Linear
    // constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto MAX_DELAY_SAMPLES = static_cast<std::uint32_t>(MAX_DELAY_TIME * md_audio::sample_rate) + 2;
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);
    //
    // Pool<TOTAL_SIZE> pool;

    // // Allpass / Delay Cubic
    // constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto MAX_DELAY_SAMPLES = static_cast<std::uint32_t>(MAX_DELAY_TIME * md_audio::sample_rate) + 3;
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);
    //
    // Pool<TOTAL_SIZE> pool;

    // // Delay
    // constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto MAX_DELAY_SAMPLES = static_cast<std::uint32_t>(MAX_DELAY_TIME * md_audio::sample_rate) + 3;
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);
    //
    // Pool<TOTAL_SIZE> pool;

    // // Tap Delay
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

    // // Reverse Delay
    // constexpr auto MAX_DELAY = 102;
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = OVERLAP * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat) + sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + OVERLAP_SIZE;
    //
    // Pool<TOTAL_SIZE> pool;

    // // Reversible Delay
    // constexpr auto MAX_DELAY = 102;
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = (OVERLAP + 1) * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat)) + OVERLAP * (sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + OVERLAP_SIZE;
    //
    // Pool<TOTAL_SIZE> pool;

    // // Pitch Shifter
    // constexpr auto MAX_SIZE = 102;
    // constexpr auto MAX_SIZE_SIZE = MAX_SIZE * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = OVERLAP * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat) + sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator));
    // constexpr auto TOTAL_SIZE = MAX_SIZE_SIZE + OVERLAP_SIZE;
    //
    // Pool<TOTAL_SIZE> pool;

    // // Variable Delay
    // constexpr auto MAX_DELAY = /*102*/ static_cast<std::uint32_t>(5 * md_audio::sample_rate);
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = OVERLAP * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat) + sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator) + sizeof(md_audio::Latch));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + OVERLAP_SIZE;
    //
    // Pool<TOTAL_SIZE> pool;

    md_audio::AllpassStatic allpass(pool, MAX_DELAY_TIME, DELAY_TIME);
    // md_audio::DelayStatic delay(pool, MAX_DELAY_TIME, DELAY_TIME);
    // md_audio::DelayLinear delay(pool, MAX_DELAY_TIME, DELAY_TIME);
    // md_audio::DelayCubic delay(pool, MAX_DELAY_TIME, DELAY_TIME);
    // md_audio::Delay delay(pool, MAX_DELAY_TIME, DELAY_TIME, md_audio::InterpolationType::cubic);
    // md_audio::TapDelayLinear delay(pool, MAX_DELAY, TAPS);
    // md_audio::TapDelay delay(pool, MAX_DELAY, TAPS, static_cast<md_audio::InterpolationType>(0));
    // md_audio::TapDelayStatic delay(pool, MAX_DELAY, TAPS);
    // md_audio::ReverseDelay delay(pool, MAX_DELAY, 50.f, OVERLAP);
    // md_audio::ReversibleDelay delay(pool, MAX_DELAY, 50.f, true, OVERLAP);
    // md_audio::Normaliser normaliser(pool, DURATION);
    // md_audio::PitchShifter shifter(pool, MAX_SIZE, 50.f, OVERLAP);
    // md_audio::VariableDelay delay(pool, MAX_DELAY, .2f * md_audio::sample_rate, .2f * md_audio::sample_rate, OVERLAP);
    md_audio::WhiteNoise noise;

    // delay.set_delay(DELAY_TIMES);

    for (std::size_t i = 0; i < 441; ++i) {
        // md_audio::MdFloat z[TAPS];

        const auto y = noise.perform();
        // const auto z = normaliser.perform(y);
        // delay.perform(y, z, TAPS);
        // delay.set_delay((y * .5 + .5) * ((.3 - .2) + .2) * md_audio::sample_rate);
        // const auto z = delay.perform(y);
        const auto z = allpass.perform(y);
        // const auto z = shifter.perform(y);

        std::cout << i << "\t" << y << "\t" << z << std::endl;

        // std::cout << i << "\t";
        //
        // for (auto i = 0; i < TAPS; ++i)
        //     std::cout << delay.read(i) << ", ";
        //     // std::cout << z[i] << ", ";
        //
        // std::cout << std::endl;
        //
        // delay.write(y);
    }
}
