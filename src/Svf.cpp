#include "Svf.hpp"

using md_audio::MdFloat;
using md_audio::Svf;

Svf::Svf() {
    set_frequency(static_cast<MdFloat>(440));
    set_r(static_cast<MdFloat>(1));
}

Svf::Svf(MdFloat frequency) {
    set_frequency(frequency);
    set_r(static_cast<MdFloat>(1));
}

Svf::Svf(MdFloat frequency, MdFloat r) {
    set_frequency(frequency);
    set_r(r);
}

std::array<MdFloat, 3> Svf::perform(MdFloat in) noexcept {
    auto g1 = m_r2 + m_g;
    auto hp = (static_cast<double>(in) - g1 * m_s1 - m_s2) * d(m_r2, m_g);

    // First integrator
    auto v1 = m_g * hp;
    auto bp = v1 + m_s1;
    m_s1 = bp + v1;

    // Second integrator
    auto v2 = m_g * bp;
    auto lp = v2 + m_s2;
    m_s2 = lp + v2;

    std::array<MdFloat, 3> out{
        static_cast<MdFloat>(lp),
        static_cast<MdFloat>(hp),
        static_cast<MdFloat>(bp)
    };

    return out;
}
