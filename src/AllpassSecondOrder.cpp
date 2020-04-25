#include "AllpassSecondOrder.hpp"

using md_audio::AllpassSecondOrder;
using md_audio::MdFloat;

AllpassSecondOrder::AllpassSecondOrder() {
    set_frequency(static_cast<MdFloat>(440));
    set_r(static_cast<MdFloat>(1));
}

AllpassSecondOrder::AllpassSecondOrder(MdFloat frequency) {
    set_frequency(frequency);
    set_r(static_cast<MdFloat>(1));
}

AllpassSecondOrder::AllpassSecondOrder(MdFloat frequency, MdFloat r) {
    set_frequency(frequency);
    set_r(r);
}

MdFloat AllpassSecondOrder::perform(MdFloat in) noexcept {
    auto x = static_cast<double>(in);

    auto bp = (m_g * (m_r2 * x - m_s2) + m_s1) * d(m_r2, m_g);

    // First integrator
    auto bp2 = bp + bp;
    m_s1 = bp2 - m_s1;

    // Second integrator
    auto v22 = m_g * bp2;
    m_s2 = m_s2 + v22;

    return x - 2. * bp;
}
