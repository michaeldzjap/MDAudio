#include "SineOscillator.hpp"
#include "Oscillator.hpp"
#include "tables.hpp"

using md_audio::SineOscillator;
using md_audio::MdFloat;
using md_audio::Oscillator;

SineOscillator::SineOscillator(MdFloat frequency) : Oscillator(frequency) {}

SineOscillator::SineOscillator(MdFloat frequency, MdFloat phase) : Oscillator(frequency, phase) {}

MdFloat SineOscillator::perform() noexcept {
    return Oscillator::perform(sine_table);
}
