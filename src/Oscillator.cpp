#include "Oscillator.hpp"
#include "utility.hpp"

using md_audio::MdFloat;
using md_audio::Oscillator;

Oscillator::Oscillator(MdFloat frequency) : m_cycles_to_increment(table_size * m_sample_duration) {
    set_frequency(frequency);
    set_phase(static_cast<MdFloat>(0));
}

Oscillator::Oscillator(MdFloat frequency, MdFloat phase) : m_cycles_to_increment(table_size * m_sample_duration) {
    set_frequency(frequency);
    set_phase(phase);
}

MdFloat Oscillator::perform(const std::array<MdFloat, table_size + 1> &table) noexcept {
    auto offset = m_phase_acc + m_phase_rate;

    while (offset < 0.) offset += static_cast<double>(table_size);
    while (offset >= table_size) offset -= static_cast<double>(table_size);

    auto z = utility::lookup(table, offset);

    m_phase_acc += m_frequency_rate;

    return z;
}

Oscillator::~Oscillator() {}
