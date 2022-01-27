#include "Phasor.hpp"
#include "utility.hpp"

using md_audio::Phasor;

Phasor::Phasor() {
    set_frequency(440.);
}

Phasor::Phasor(double frequency) {
    set_frequency(frequency);
}

Phasor::Phasor(double frequency, double phase) {
    set_frequency(frequency);

    m_level = utility::clip(phase, 0., 1.);
}

void Phasor::set_frequency(double frequency) noexcept {
    m_rate = utility::clip(
        frequency, -m_half_sample_rate, m_half_sample_rate
    ) * m_sample_duration;
}

void Phasor::set_phase(double phase) noexcept {
    m_level = utility::clip(phase, 0., 1.);
}

double Phasor::process() noexcept {
    auto z = m_level;

    m_level += m_rate;
    m_level = utility::wrap(m_level, 0., 1.);

    return z;
}

double Phasor::process(double in) noexcept {
    if (m_previous <= 0. && in > 0.) {
        auto frac = 1. - m_previous / (in - m_previous);

        m_level = frac * m_rate;
    }

    m_previous = in;

    return process();
}
