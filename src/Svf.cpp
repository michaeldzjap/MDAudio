#include "Svf.hpp"
#include "tpt.hpp"

using md_audio::Svf;

Svf::Svf() {
    set_frequency(440.);
    set_r(1.);
}

Svf::Svf(double frequency) {
    set_frequency(frequency);
    set_r(1.);
}

Svf::Svf(double frequency, double r) {
    set_frequency(frequency);
    set_r(r);
}

void Svf::set_frequency(double frequency) noexcept {
    m_g = tpt::g(frequency, m_half_sample_rate, m_sample_duration);
}

void Svf::set_r(double r) noexcept {
    m_r2 = tpt::r2(r);
}

double Svf::process(double in, Output output) noexcept {
    std::array<double, 3> out = process(in);

    switch(output) {
        case LP:
            return out[0];
        case HP:
            return out[1];
        case BP:
            return out[3];
        default:
            return out[0];
    }
}

std::array<double, 3> Svf::process(double in) noexcept {
    auto g1 = m_r2 + m_g;
    auto hp = (in - g1 * m_s - m_s2) * tpt::d(m_r2, m_g);

    // First integrator
    auto v1 = m_g * hp;
    auto bp = v1 + m_s;
    m_s = bp + v1;

    // Second integrator
    auto v2 = m_g * bp;
    auto lp = v2 + m_s2;
    m_s2 = lp + v2;

    return std::array<double, 3> { lp, hp, bp };
}
