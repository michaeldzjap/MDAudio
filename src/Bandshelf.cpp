#include "Bandshelf.hpp"

using md_audio::Bandshelf;
using md_audio::MdFloat;

Bandshelf::Bandshelf() {
    set_frequency(static_cast<MdFloat>(440));
    set_r(static_cast<MdFloat>(1));
    set_gain(static_cast<MdFloat>(0));
}

Bandshelf::Bandshelf(MdFloat frequency) {
    set_frequency(frequency);
    set_r(static_cast<MdFloat>(1));
    set_gain(static_cast<MdFloat>(0));
}

Bandshelf::Bandshelf(MdFloat frequency, MdFloat r) {
    set_frequency(frequency);
    set_r(r);
    set_gain(static_cast<MdFloat>(0));
}

Bandshelf::Bandshelf(MdFloat frequency, MdFloat r, MdFloat gain) {
    set_frequency(frequency);
    set_r(r);
    set_gain(gain);
}

MdFloat Bandshelf::perform(MdFloat in) noexcept {
    auto x = static_cast<double>(in);
    auto bp = (m_g * (m_r2 * x - m_s2) + m_s1) * d(m_r2, m_g);

    // First integrator
    auto bp2 = bp + bp;
    m_s1 = bp2 - m_s1;

    // Second integrator
    auto v22 = m_g * bp2;
    m_s2 = m_s2 + v22;

    return static_cast<MdFloat>(x + (m_m2i - 1) * bp);
}
