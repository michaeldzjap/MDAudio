#include "LowpassSecondOrder.hpp"

using md_audio::LowpassSecondOrder;
using md_audio::MdFloat;

LowpassSecondOrder::LowpassSecondOrder() {
    set_frequency(static_cast<MdFloat>(440));
    set_r(static_cast<MdFloat>(1));
}

LowpassSecondOrder::LowpassSecondOrder(MdFloat frequency) {
    set_frequency(frequency);
    set_r(static_cast<MdFloat>(1));
}

LowpassSecondOrder::LowpassSecondOrder(MdFloat frequency, MdFloat r) {
    set_frequency(frequency);
    set_r(r);
}

MdFloat LowpassSecondOrder::perform(MdFloat in) noexcept {
    auto bp = (m_g * (static_cast<double>(in) - m_s2) + m_s1) * d(m_r2, m_g);

    // First integrator
    auto v1 = bp - m_s1;
    m_s1 = bp + v1;

    // Second integrator
    auto v2 = m_g * bp;
    auto lp = v2 + m_s2;
    m_s2 = lp + v2;

    return static_cast<MdFloat>(lp);
}
