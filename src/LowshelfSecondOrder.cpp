#include <array>
#include "LowshelfSecondOrder.hpp"

using md_audio::LowshelfSecondOrder;

LowshelfSecondOrder::LowshelfSecondOrder() {
    set_frequency(440.);
    set_r(1.);
    set_gain(0.);
}

LowshelfSecondOrder::LowshelfSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
    set_gain(0.);
}

LowshelfSecondOrder::LowshelfSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
    set_gain(0.);
}

LowshelfSecondOrder::LowshelfSecondOrder(double frequency, double r, double gain) {
    set_frequency(frequency);
    set_r(r);
    set_gain(gain);
}

double LowshelfSecondOrder::process(double in) noexcept {
    std::array<double, 3> out = Svf::process(in);

    return out[0] * m_m4 + m_r2 * m_m2 * out[2] + out[1];
}
