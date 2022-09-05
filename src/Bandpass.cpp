#include "Bandpass.hpp"

using md_audio::Bandpass;

Bandpass::Bandpass() {
    set_frequency(440.);
    set_r(1.);
}

Bandpass::Bandpass(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

Bandpass::Bandpass(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

double Bandpass::process(double in) noexcept {
    return Svf::process(m_r2 * in, Output::BP);
}
