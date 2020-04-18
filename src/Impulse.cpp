#include "Impulse.hpp"

using md_audio::Impulse;
using md_audio::MdFloat;

Impulse::Impulse(MdFloat frequency) {
    set_frequency(frequency);
}

MdFloat Impulse::perform(void) noexcept {
    MdFloat z;

    if (m_phase >= 1.) {
        m_phase -= 1.;
        z = static_cast<MdFloat>(1);
    } else {
        z = static_cast<MdFloat>(0);
    }

    m_phase += m_rate;

    return z;
}
