#include "LowpassFirstOrder.hpp"

using md_audio::LowpassFirstOrder;

LowpassFirstOrder::LowpassFirstOrder() {
    set_frequency(440.);
}

LowpassFirstOrder::LowpassFirstOrder(double frequency) {
    set_frequency(frequency);
}

double LowpassFirstOrder::process(double in) noexcept {
    auto v = (in - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return y;
}
