#include "LowpassSecondOrder.hpp"

using md_audio::LowpassSecondOrder;

LowpassSecondOrder::LowpassSecondOrder() {
    set_frequency(440.);
    set_r(1.);
}

LowpassSecondOrder::LowpassSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

LowpassSecondOrder::LowpassSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double LowpassSecondOrder::process(double in) noexcept {
    return Svf::process(in, Output::LP);
}
