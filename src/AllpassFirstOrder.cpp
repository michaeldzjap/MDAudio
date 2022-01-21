#include "AllpassFirstOrder.hpp"

using md_audio::AllpassFirstOrder;

AllpassFirstOrder::AllpassFirstOrder() {
    set_frequency(440.);
}

AllpassFirstOrder::AllpassFirstOrder(double frequency) {
    set_frequency(frequency);
}

void AllpassFirstOrder::set_frequency(double frequency) noexcept {
    auto _g = g(frequency);
    m_h = 2. * _g / (1. + _g);
}

double AllpassFirstOrder::process(double in) noexcept {
    auto xs = in - m_s;

    m_s = m_s + xs * m_h;

    return m_s - xs;
}
