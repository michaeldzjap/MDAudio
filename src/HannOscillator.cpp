#include "HannOscillator.hpp"
#include "Oscillator.hpp"
#include "tables.hpp"

using md_audio::HannOscillator;
using md_audio::MdFloat;
using md_audio::Oscillator;

HannOscillator::HannOscillator(MdFloat frequency) : Oscillator(frequency) {}

HannOscillator::HannOscillator(MdFloat frequency, MdFloat phase) : Oscillator(frequency, phase) {}

MdFloat HannOscillator::perform() noexcept {
    return Oscillator::perform(hann_table);
}
