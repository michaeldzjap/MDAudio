#include "Bandshelf.hpp"

using md_audio::Bandshelf;

Bandshelf::Bandshelf() {
    set_frequency(440.);
    set_r(1.);
    set_gain(0.);
}

Bandshelf::Bandshelf(double frequency) {
    set_frequency(frequency);
    set_r(1.);
    set_gain(0.);
}

Bandshelf::Bandshelf(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
    set_gain(0.);
}

Bandshelf::Bandshelf(double frequency, double r, double gain) {
    set_frequency(frequency);
    set_r(r);
    set_gain(gain);
}

void Bandshelf::set_gain(double gain) noexcept {
    m_m2i = 1. / m2(-gain);
}

double Bandshelf::process(double in) noexcept {
    auto bp = (m_g * (m_r2 * in - m_s2) + m_s) * d(m_r2, m_g);

    // First integrator
    auto bp2 = bp + bp;
    m_s = bp2 - m_s;

    // Second integrator
    auto v22 = m_g * bp2;
    m_s2 = m_s2 + v22;

    return in + (m_m2i - 1) * bp;
}
