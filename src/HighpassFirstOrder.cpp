#include "HighpassFirstOrder.hpp"

using md_audio::HighpassFirstOrder;

HighpassFirstOrder::HighpassFirstOrder() {
    set_frequency(440.);
}

HighpassFirstOrder::HighpassFirstOrder(double frequency) {
    set_frequency(frequency);
}

double HighpassFirstOrder::process(double in) noexcept {
    auto v = (in - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return in - y;
}
