#include "LowpassFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::LowpassFirstOrder;

LowpassFirstOrder::LowpassFirstOrder() {
    set_frequency(440.);
}

LowpassFirstOrder::LowpassFirstOrder(double frequency) {
    set_frequency(frequency);
}

void LowpassFirstOrder::set_frequency(double frequency) noexcept {
    auto g = tpt::g(frequency, m_half_sample_rate, m_sample_duration);
    m_h = g / (1. + g);
}

double LowpassFirstOrder::process(double in) noexcept {
    auto v = (in - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return y;
}
