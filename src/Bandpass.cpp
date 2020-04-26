#include "Bandpass.hpp"

using md_audio::Bandpass;
using md_audio::MdFloat;

Bandpass::Bandpass() {
    set_frequency(static_cast<MdFloat>(440));
    set_r(static_cast<MdFloat>(1));
}

Bandpass::Bandpass(MdFloat frequency) {
    set_frequency(frequency);
    set_r(static_cast<MdFloat>(1));
}

Bandpass::Bandpass(MdFloat frequency, MdFloat r) {
    set_frequency(frequency);
    set_r(r);
}

MdFloat Bandpass::perform(MdFloat in) noexcept {
    const double bp = (m_g * (m_r2 * static_cast<double>(in) - m_s2) + m_s1) * d(m_r2, m_g);

    // First integrator
    auto bp2 = bp + bp;
    m_s1 = bp2 - m_s1;

    // Second integrator
    auto v22 = m_g * bp2;
    m_s2 = m_s2 + v22;

    return static_cast<MdFloat>(bp);
}
