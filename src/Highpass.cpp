#include "Highpass.hpp"

using md_audio::Highpass;
using md_audio::MdFloat;

Highpass::Highpass() {
    set_frequency(static_cast<MdFloat>(440));
}

Highpass::Highpass(MdFloat frequency) {
    set_frequency(frequency);
}

MdFloat Highpass::perform(MdFloat in) noexcept {
    const double y = (static_cast<double>(in) - m_s) * m_h;

    m_s = m_s + y * m_g2;

    return static_cast<MdFloat>(y);
}
