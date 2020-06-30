#include "Phasor.hpp"

using md_audio::MdFloat;
using md_audio::Phasor;

Phasor::Phasor() {
    set_frequency(static_cast<MdFloat>(440));
}

Phasor::Phasor(MdFloat frequency) {
    set_frequency(frequency);
}

Phasor::Phasor(MdFloat frequency, MdFloat phase) {
    set_frequency(frequency);
    m_level = utility::clip(phase, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
}

MdFloat Phasor::perform(void) noexcept {
    auto z = m_level;

    m_level += m_rate;
    m_level = utility::wrap(m_level, 0., 1.);

    return static_cast<MdFloat>(z);
}

MdFloat Phasor::perform(MdFloat in) noexcept {
    if (m_previous <= static_cast<MdFloat>(0) && in > static_cast<MdFloat>(0)) {
        auto frac = static_cast<MdFloat>(1) - m_previous / (in - m_previous);

        m_level = frac * m_rate;
    }

    auto z = m_level;

    m_level += m_rate;
    m_level = utility::wrap(m_level, 0., 1.);

    m_previous = in;

    return static_cast<MdFloat>(z);
}
