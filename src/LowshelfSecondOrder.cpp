#include "LowshelfSecondOrder.hpp"
#include "tpt.hpp"

using md_audio::LowshelfSecondOrder;

LowshelfSecondOrder::LowshelfSecondOrder() {
    set_frequency(440.);
    set_r(1.);
    set_gain(0.);
}

LowshelfSecondOrder::LowshelfSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
    set_gain(0.);
}

LowshelfSecondOrder::LowshelfSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
    set_gain(0.);
}

LowshelfSecondOrder::LowshelfSecondOrder(double frequency, double r, double gain) {
    set_frequency(frequency);
    set_r(r);
    set_gain(gain);
}

double LowshelfSecondOrder::process(double in) noexcept {
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

    return m_m4 * lp + m_m2 * m_r2 * bp + hp;
}
