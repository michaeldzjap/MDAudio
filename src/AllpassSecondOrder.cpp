#include "AllpassSecondOrder.hpp"
#include "tpt.hpp"

using md_audio::AllpassSecondOrder;

AllpassSecondOrder::AllpassSecondOrder() {
    set_frequency(440.);
    set_r(1.);
}

AllpassSecondOrder::AllpassSecondOrder(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

AllpassSecondOrder::AllpassSecondOrder(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double AllpassSecondOrder::process(double in) noexcept {
    auto bp = Svf::process(m_r2 * in, Output::BP);

    return in - 2. * bp;
}
