#include "Lowpass.hpp"

using md_audio::Lowpass;
using md_audio::MdFloat;

Lowpass::Lowpass() {
    set_frequency(static_cast<MdFloat>(440));
}

Lowpass::Lowpass(MdFloat frequency) {
    set_frequency(frequency);
}

MdFloat Lowpass::perform(MdFloat in) noexcept {
    const double v = (static_cast<double>(in) - m_s) * m_h;
    const double y = v + m_s;

    m_s = y + v;

    return static_cast<MdFloat>(y);
}
