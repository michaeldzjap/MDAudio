#include "AllpassFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::AllpassFirstOrder;

AllpassFirstOrder::AllpassFirstOrder() {
    set_frequency(440.);
}

AllpassFirstOrder::AllpassFirstOrder(double frequency) {
    set_frequency(frequency);
}

void AllpassFirstOrder::set_frequency(double frequency) noexcept {
    auto g = tpt::g(frequency, m_half_sample_rate, m_sample_duration);
    m_h = 2. * g / (1. + g);
}

double AllpassFirstOrder::process(double in) noexcept {
    auto xs = in - m_s;

    m_s = m_s + xs * m_h;

    return m_s - xs;
}
