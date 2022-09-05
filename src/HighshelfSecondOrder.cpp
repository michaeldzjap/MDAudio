#include <array>
#include "HighshelfSecondOrder.hpp"

using md_audio::HighshelfSecondOrder;

HighshelfSecondOrder::HighshelfSecondOrder() {
    set_frequency(440.);
    set_r(1.);
    set_gain(0.);
}

HighshelfSecondOrder::HighshelfSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
    set_gain(0.);
}

HighshelfSecondOrder::HighshelfSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
    set_gain(0.);
}

HighshelfSecondOrder::HighshelfSecondOrder(double frequency, double r, double gain) {
    set_frequency(frequency);
    set_r(r);
    set_gain(gain);
}

double HighshelfSecondOrder::process(double in) noexcept {
    std::array<double, 3> out = Svf::process(in);

    return out[0] + m_m2 * m_r2 * out[2] + m_m4 * out[1];
}
