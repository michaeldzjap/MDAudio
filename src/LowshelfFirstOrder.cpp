#include "LowshelfFirstOrder.hpp"

using md_audio::LowshelfFirstOrder;

LowshelfFirstOrder::LowshelfFirstOrder() {
    set_frequency(440.);
    set_gain(0.);
}

LowshelfFirstOrder::LowshelfFirstOrder(double frequency) {
    set_frequency(frequency);
    set_gain(0.);
}

LowshelfFirstOrder::LowshelfFirstOrder(double frequency, double gain) {
    set_frequency(frequency);
    set_gain(gain);
}

void LowshelfFirstOrder::set_frequency(double frequency) noexcept {
    auto _g = g(frequency);
    m_h = _g / (1. + _g);
}

void LowshelfFirstOrder::set_gain(double gain) noexcept {
    m_m2i = 1. / m2(-gain);
}

double LowshelfFirstOrder::process(double in) noexcept {
    auto v = (in - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return m_m2i * y + in - y;
}
