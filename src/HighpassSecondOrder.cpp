#include "HighpassSecondOrder.hpp"
#include "tpt.hpp"

using md_audio::HighpassSecondOrder;

HighpassSecondOrder::HighpassSecondOrder() {
    set_frequency(440.);
    set_r(1.);
}

HighpassSecondOrder::HighpassSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

HighpassSecondOrder::HighpassSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double HighpassSecondOrder::process(double in) noexcept {
    auto g1 = m_r2 + m_g;
    auto hp = (in - g1 * m_s - m_s2) * tpt::d(m_r2, m_g);

    // First integrator
    auto v1 = m_g * hp;
    auto bp = v1 + m_s;
    m_s = bp + v1;

    // Second integrator
    auto v2 = m_g * bp;
    auto lp = v2 + m_s2;
    m_s2 = lp + v2;

    return hp;
}
