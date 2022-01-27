#include "HighpassFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::HighpassFirstOrder;

HighpassFirstOrder::HighpassFirstOrder() {
    set_frequency(440.);
}

HighpassFirstOrder::HighpassFirstOrder(double frequency) {
    set_frequency(frequency);
}

void HighpassFirstOrder::set_frequency(double frequency) noexcept {
    auto g = tpt::g(frequency, m_half_sample_rate, m_sample_duration);
    m_g2 = g + g;
    m_h = 1. / (1. + g);
}

double HighpassFirstOrder::process(double in) noexcept {
    auto y = (in - m_s) * m_h;

    m_s = m_s + y * m_g2;

    return y;
}
