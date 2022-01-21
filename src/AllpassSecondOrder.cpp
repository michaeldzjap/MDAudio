#include "AllpassSecondOrder.hpp"

using md_audio::AllpassSecondOrder;

AllpassSecondOrder::AllpassSecondOrder() {
    set_frequency(440.);
    set_r(1.);
}

AllpassSecondOrder::AllpassSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

AllpassSecondOrder::AllpassSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double AllpassSecondOrder::process(double in) noexcept {
    auto bp = (m_g * (m_r2 * in - m_s2) + m_s) * d(m_r2, m_g);

    // First integrator
    auto bp2 = bp + bp;
    m_s = bp2 - m_s;

    // Second integrator
    auto v22 = m_g * bp2;
    m_s2 = m_s2 + v22;

    return in - 2. * bp;
}
