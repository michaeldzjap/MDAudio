#include <cmath>
#include "TiltFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::TiltFirstOrder;

TiltFirstOrder::TiltFirstOrder() {
    set_frequency(440.);
    set_gain(0.);
}

TiltFirstOrder::TiltFirstOrder(double frequency) {
    set_frequency(frequency);
    set_gain(0.);
}

TiltFirstOrder::TiltFirstOrder(double frequency, double gain) {
    set_frequency(frequency);
    set_gain(gain);
}

void TiltFirstOrder::set_gain(double gain) noexcept {
    m_m = std::sqrt(tpt::m2(gain));
    m_mi = 1. / m_m;
}

double TiltFirstOrder::process(double in) noexcept {
    auto v = (in - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return m_mi * y + m_m * (in - y);
}
