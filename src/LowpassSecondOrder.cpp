#include "LowpassSecondOrder.hpp"
#include "tpt.hpp"

using md_audio::LowpassSecondOrder;

LowpassSecondOrder::LowpassSecondOrder() {
    set_frequency(440.);
    set_r(1.);
}

LowpassSecondOrder::LowpassSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

LowpassSecondOrder::LowpassSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double LowpassSecondOrder::process(double in) noexcept {
    auto bp = (m_g * (in - m_s2) + m_s) * tpt::d(m_r2, m_g);

    // First integrator
    auto v1 = bp - m_s;
    m_s = bp + v1;

    // Second integrator
    auto v2 = m_g * bp;
    auto lp = v2 + m_s2;
    m_s2 = lp + v2;

    return lp;
}
