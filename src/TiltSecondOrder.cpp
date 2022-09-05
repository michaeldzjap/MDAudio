#include <array>
#include "TiltSecondOrder.hpp"
#include "tpt.hpp"

using md_audio::TiltSecondOrder;

TiltSecondOrder::TiltSecondOrder() {
    set_frequency(440.);
    set_r(1.);
    set_gain(0.);
}

TiltSecondOrder::TiltSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
    set_gain(0.);
}

TiltSecondOrder::TiltSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
    set_gain(0.);
}

TiltSecondOrder::TiltSecondOrder(double frequency, double r, double gain) {
    set_frequency(frequency);
    set_r(r);
    set_gain(gain);
}

void TiltSecondOrder::set_gain(double gain) noexcept {
    m_m2 = tpt::m2(gain);
    m_m4 = 1. / m_m2;
}

double TiltSecondOrder::process(double in) noexcept {
    std::array<double, 3> out = Svf::process(in);

    return m_m4 * out[0] + m_r2 * out[2] + m_m2 * out[1];
}
