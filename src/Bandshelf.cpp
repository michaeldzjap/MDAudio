#include "Bandshelf.hpp"
#include "tpt.hpp"

using md_audio::Bandshelf;

Bandshelf::Bandshelf() {
    set_frequency(440.);
    set_r(1.);
    set_gain(0.);
}

Bandshelf::Bandshelf(double frequency) {
    set_frequency(frequency);
    set_r(1.);
    set_gain(0.);
}

Bandshelf::Bandshelf(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
    set_gain(0.);
}

Bandshelf::Bandshelf(double frequency, double r, double gain) {
    set_frequency(frequency);
    set_r(r);
    set_gain(gain);
}

void Bandshelf::set_gain(double gain) noexcept {
    m_m2i = tpt::m2(gain);
}

double Bandshelf::process(double in) noexcept {
    auto bp = Svf::process(m_r2 * in, Output::BP);

    return in + (m_m2i - 1) * bp;
}
