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

double LowshelfFirstOrder::process(double in) noexcept {
    auto v = (in - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return m_m2 * y + in - y;
}
