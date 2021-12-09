#include "Oscillator.hpp"
#include "utility.hpp"

using md_audio::Oscillator;
using md_audio::utility::clip;
using md_audio::utility::lookup;

Oscillator::Oscillator(double frequency) :
    m_phase_acc(0.),
    m_cycles_to_increment(TABLE_SIZE * m_sample_duration)
{
    set_frequency(frequency);
    set_phase(0.);
}

Oscillator::Oscillator(double frequency, double phase) :
    m_phase_acc(0.),
    m_cycles_to_increment(TABLE_SIZE * m_sample_duration)
{
    set_frequency(frequency);
    set_phase(phase);
}

void Oscillator::set_frequency(double frequency) noexcept {
    m_frequency_rate = m_cycles_to_increment * clip<double>(
        frequency, -m_half_sample_rate, m_half_sample_rate
    );
}

void Oscillator::set_phase(double phase) noexcept {
    m_phase_rate = RADIANS_TO_INCREMENT * phase;
}

double Oscillator::process(const std::array<double, TABLE_SIZE + 1>& table) noexcept {
    auto offset = m_phase_acc + m_phase_rate;

    while (offset < 0.) offset += TABLE_SIZE;
    while (offset >= TABLE_SIZE) offset -= TABLE_SIZE;

    auto z = lookup(table, offset);

    m_phase_acc += m_frequency_rate;

    return z;
}
