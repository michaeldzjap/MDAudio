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
#include "SampleRate.hpp"
#include "TapDelay.hpp"
#include "TapDelayCubic.hpp"
#include "TapDelayLinear.hpp"
#include "TapDelayStatic.hpp"
#include "VariableDelay.hpp"
#include "WhiteNoise.hpp"
#include "constants.hpp"
#include "memory/StaticPool.hpp"
#include "types.hpp"
#include <iomanip>
#include <iostream>

template <std::size_t Size>
using Pool = md_audio::memory::StaticPool<Size>;

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(9);

    // md_audio::TapDelay::set_sample_rate(44100.);
    // std::cout << md_audio::Reverb::get_sample_rate() << std::endl;

    // // Delay
    // constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto MAX_DELAY_SAMPLES = static_cast<std::uint32_t>(MAX_DELAY_TIME * md_audio::sample_rate) + 3;
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);
    //
    // Pool<TOTAL_SIZE> pool;

    // // Tap Delay
    // constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.001);
    // constexpr auto MAX_DELAY_SAMPLES = static_cast<std::uint32_t>(MAX_DELAY_TIME * md_audio::sample_rate) + 2;
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);
    // constexpr auto TAPS = 4;
    // constexpr auto TAPS_SIZE = TAPS * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + TAPS_SIZE;
    // constexpr md_audio::MdFloat DELAY_TIMES[TAPS] = {0.001, 0.0005, 0.00007, 0.000251};
    //
    // Pool<TOTAL_SIZE> pool;

    // // Normaliser
    // constexpr auto DURATION_TIME = static_cast<md_audio::MdFloat>(.1);
    // constexpr auto DURATION_SAMPLES = static_cast<std::uint32_t>(DURATION_TIME * md_audio::sample_rate);
    // constexpr auto TOTAL_SIZE = DURATION_SAMPLES * sizeof(md_audio::MdFloat) * 3;
    //
    // Pool<TOTAL_SIZE> pool;

    // // Reverse Delay
    // constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.02);
    // constexpr auto SIZE_TIME = static_cast<md_audio::MdFloat>(.02);
    // constexpr auto MAX_DELAY_SAMPLES = md_audio::utility::ceil(MAX_DELAY_TIME * md_audio::sample_rate) + 1;
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = OVERLAP * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat) + sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + OVERLAP_SIZE + sizeof(md_audio::ReverseDelay);
    //
    // Pool<TOTAL_SIZE> pool;

    // // Reversible Delay
    // constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.02);;
    // constexpr auto SIZE_TIME = static_cast<md_audio::MdFloat>(.02);
    // constexpr auto MAX_DELAY_SAMPLES = md_audio::utility::ceil(MAX_DELAY_TIME * md_audio::sample_rate) + 1;
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = (OVERLAP + 1) * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat)) + OVERLAP * (sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + OVERLAP_SIZE + 29;
    //
    // Pool<TOTAL_SIZE> pool;

    // // Pitch Shifter
    // constexpr auto MAX_SIZE_TIME = static_cast<md_audio::MdFloat>(.02);
    // constexpr auto SIZE_TIME = static_cast<md_audio::MdFloat>(.02);
    // constexpr auto MAX_SIZE_SAMPLES = md_audio::utility::ceil(MAX_SIZE_TIME * md_audio::sample_rate) + 1;
    // constexpr auto MAX_SIZE_SIZE = MAX_SIZE_SAMPLES * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = OVERLAP * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat) + sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator));
    // constexpr auto TOTAL_SIZE = MAX_SIZE_SIZE + OVERLAP_SIZE + 60;
    //
    // Pool<TOTAL_SIZE> pool;

    // // Variable Delay
    // constexpr auto MAX_DELAY_TIME = static_cast<md_audio::MdFloat>(.02);
    // constexpr auto DELAY_TIME = static_cast<md_audio::MdFloat>(.02);
    // constexpr auto MAX_DELAY_SAMPLES = md_audio::utility::ceil(MAX_DELAY_TIME * md_audio::sample_rate);
    // constexpr auto MAX_DELAY_SIZE = MAX_DELAY_SAMPLES * sizeof(md_audio::MdFloat);
    // constexpr auto OVERLAP = 2;
    // constexpr auto OVERLAP_SIZE = OVERLAP * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat) + sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator) + sizeof(md_audio::Latch));
    // constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + OVERLAP_SIZE;
    //
    // Pool<TOTAL_SIZE> pool;

    // Reverb
    constexpr auto TOTAL_SIZE = static_cast<std::uint32_t>(
        md_audio::utility::seconds_to_samples(md_audio::ReverbConfig::max_pre_delay_time, static_cast<md_audio::MdFloat>(md_audio::sample_rate)) * sizeof(md_audio::MdFloat) // Reversible delay memory
        + (sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator)) * md_audio::ReverbConfig::overlap_pre_delay + (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat)) * (md_audio::ReverbConfig::overlap_pre_delay + 1)
        + (md_audio::utility::seconds_to_samples(md_audio::ReverbConfig::max_pitch_shift_window_time, static_cast<md_audio::MdFloat>(md_audio::sample_rate)) + 1) * md_audio::ReverbConfig::output_count * sizeof(md_audio::MdFloat) // Pitch shifter memory
        + (sizeof(md_audio::Phasor) + sizeof(md_audio::HannOscillator) + sizeof(std::uint32_t) + sizeof(md_audio::MdFloat)) * md_audio::ReverbConfig::overlap_shifter * md_audio::ReverbConfig::output_count
        + md_audio::utility::sum(md_audio::utility::seconds_to_samples(md_audio::ReverbConfig::max_allpass_times, static_cast<md_audio::MdFloat>(md_audio::sample_rate))) * sizeof(md_audio::MdFloat) // Allpass memory
        + md_audio::utility::sum(md_audio::utility::seconds_to_samples(md_audio::ReverbConfig::max_delay_times, static_cast<md_audio::MdFloat>(md_audio::sample_rate), static_cast<md_audio::MdFloat>(1))) * md_audio::ReverbConfig::serial_stages * sizeof(md_audio::MdFloat) // Delay memory
        + md_audio::utility::seconds_to_samples(md_audio::ReverbConfig::normaliser_duration_time, static_cast<md_audio::MdFloat>(md_audio::sample_rate)) * 3 * md_audio::ReverbConfig::delay_count * sizeof(md_audio::MdFloat) // Normaliser memory
        + sizeof(md_audio::ReversibleDelay) + sizeof(md_audio::PitchShifter) * md_audio::ReverbConfig::output_count
    );

    Pool<TOTAL_SIZE> pool;

    // md_audio::AllpassStatic allpass(pool, MAX_DELAY_TIME, DELAY_TIME);
    // md_audio::DelayStatic delay(pool, MAX_DELAY_TIME, DELAY_TIME);
    // md_audio::DelayLinear delay(pool, MAX_DELAY_TIME, DELAY_TIME);
    // md_audio::DelayCubic delay(pool, MAX_DELAY_TIME, DELAY_TIME);
    // md_audio::Delay delay(pool, MAX_DELAY_TIME, DELAY_TIME, md_audio::InterpolationType::cubic);
    // md_audio::TapDelayLinear delay(pool, MAX_DELAY_TIME, TAPS);
    // md_audio::TapDelay delay(pool, MAX_DELAY, TAPS, static_cast<md_audio::InterpolationType>(0));
    // md_audio::TapDelayCubic delay(pool, MAX_DELAY_TIME, TAPS);
    // md_audio::ReverseDelay delay(pool, MAX_DELAY_TIME, SIZE_TIME, OVERLAP);
    // md_audio::ReversibleDelay delay(pool, MAX_DELAY_TIME, SIZE_TIME, true, OVERLAP);
    // md_audio::Normaliser normaliser(pool, DURATION_TIME);
    // md_audio::PitchShifter shifter(pool, MAX_SIZE_TIME, SIZE_TIME, OVERLAP);
    // md_audio::VariableDelay delay(pool, MAX_DELAY_TIME, DELAY_TIME, DELAY_TIME, OVERLAP);
    md_audio::Reverb reverb(pool);
    md_audio::WhiteNoise noise;

    // delay.set_delay(DELAY_TIMES);
    reverb.set_mix(1.f);
    reverb.set_absorb(0.f);
    // reverb.set_shimmer(1.f);

    for (std::size_t i = 0; i < 44100; ++i) {
        // md_audio::MdFloat z[TAPS];

        // const auto y = noise.perform();
        const auto y = 1.f;
        // const auto z = normaliser.perform(y);
        // delay.perform(y, z, TAPS);
        // delay.set_delay((y * .5 + .5) * ((.3 - .2) + .2) * md_audio::sample_rate);
        // const auto z = delay.perform(y);
        // const auto z = allpass.perform(y);
        // const auto z = shifter.perform(y);
        // const auto z = 1;
        const auto z = reverb.perform(y);

        // std::cout << i << "\t" << y << "\t" << z << std::endl;
        std::cout << i << "\t" << y << "\t" << z[0] << "\t" << z[1] << std::endl;

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
