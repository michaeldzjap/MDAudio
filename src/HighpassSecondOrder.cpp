#include "HighpassSecondOrder.hpp"

using md_audio::HighpassSecondOrder;

HighpassSecondOrder::HighpassSecondOrder() {
    set_frequency(440.);
    set_r(1.);
}

HighpassSecondOrder::HighpassSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

HighpassSecondOrder::HighpassSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double HighpassSecondOrder::process(double in) noexcept {
    return Svf::process(in, Output::HP);
}
