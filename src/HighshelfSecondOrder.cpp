#include "HighshelfSecondOrder.hpp"

using md_audio::HighShelfSecondOrder;
using md_audio::MdFloat;

HighShelfSecondOrder::HighShelfSecondOrder() {
    set_frequency(static_cast<MdFloat>(440));
    set_r(static_cast<MdFloat>(1));
    set_gain(static_cast<MdFloat>(0));
}

HighShelfSecondOrder::HighShelfSecondOrder(MdFloat frequency) {
    set_frequency(frequency);
    set_r(static_cast<MdFloat>(1));
    set_gain(static_cast<MdFloat>(0));
}

HighShelfSecondOrder::HighShelfSecondOrder(MdFloat frequency, MdFloat r) {
    set_frequency(frequency);
    set_r(r);
    set_gain(static_cast<MdFloat>(0));
}

HighShelfSecondOrder::HighShelfSecondOrder(MdFloat frequency, MdFloat r, MdFloat gain) {
    set_frequency(frequency);
    set_r(r);
    set_gain(gain);
}

MdFloat HighShelfSecondOrder::perform(MdFloat in) noexcept {
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

    return static_cast<MdFloat>(lp + m_m2 * m_r2 * bp + m_m4 * hp);
}
