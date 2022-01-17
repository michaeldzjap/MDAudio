#include "Bandpass.hpp"

using md_audio::Bandpass;

Bandpass::Bandpass() {
    set_frequency(440.);
    set_r(1.);
}

Bandpass::Bandpass(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

Bandpass::Bandpass(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double Bandpass::process(double in) noexcept {
    const double bp = (m_g * (m_r2 * in - m_s2) + m_s) * d(m_r2, m_g);

    // First integrator
    auto bp2 = bp + bp;
    m_s = bp2 - m_s;

    // Second integrator
    auto v22 = m_g * bp2;
    m_s2 = m_s2 + v22;

    return bp;
}
