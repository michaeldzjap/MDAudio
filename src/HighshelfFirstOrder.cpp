#include "HighshelfFirstOrder.hpp"

using md_audio::HighshelfFirstOrder;

HighshelfFirstOrder::HighshelfFirstOrder() {
    set_frequency(440.);
    set_gain(0.);
}

HighshelfFirstOrder::HighshelfFirstOrder(double frequency) {
    set_frequency(frequency);
    set_gain(0.);
}

HighshelfFirstOrder::HighshelfFirstOrder(double frequency, double gain) {
    set_frequency(frequency);
    set_gain(gain);
}

double HighshelfFirstOrder::process(double in) noexcept {
    auto v = (in - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return y + m_m2 * (in - y);
}
