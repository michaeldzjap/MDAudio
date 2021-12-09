#include "HannOscillator.hpp"
#include "tables.hpp"

using md_audio::HannOscillator;
using md_audio::Oscillator;

HannOscillator::HannOscillator(double frequency) : Oscillator(frequency) {}

HannOscillator::HannOscillator(double frequency, double phase) : Oscillator(frequency, phase) {}

double HannOscillator::process() noexcept {
    return Oscillator::process(hann_table);
}
