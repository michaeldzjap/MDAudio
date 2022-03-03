#include "Bandstop.hpp"

using md_audio::Bandstop;

Bandstop::Bandstop() {
    set_frequency(440.);
    set_r(1.);
}

Bandstop::Bandstop(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

Bandstop::Bandstop(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double Bandstop::process(double in) noexcept {
    auto bp = Svf::process(m_r2 * in, Output::BP);

    return in - bp;
}
