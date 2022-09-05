#include "SineOscillator.hpp"
#include "tables.hpp"

using md_audio::SineOscillator;

SineOscillator::SineOscillator() : Oscillator(440.) {}

SineOscillator::SineOscillator(double frequency) : Oscillator(frequency) {}

SineOscillator::SineOscillator(double frequency, double phase) : Oscillator(frequency, phase) {}

double SineOscillator::process() noexcept {
    return Oscillator::process(sine_table);
}
