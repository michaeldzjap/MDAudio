#include "Highshelf.hpp"
#include "Shelving.hpp"

using md_audio::Highshelf;
using md_audio::MdFloat;
using md_audio::Shelving;

Highshelf::Highshelf() {
    set_frequency(static_cast<MdFloat>(440));
}

Highshelf::Highshelf(MdFloat frequency) {
    set_frequency(frequency);
}

Highshelf::Highshelf(MdFloat frequency, MdFloat gain) : Shelving(gain) {
    set_frequency(frequency);
}

MdFloat Highshelf::perform(MdFloat in) noexcept {
    const double x = static_cast<double>(in);
    const double v = (x - m_s) * m_h;
    const double y = v + m_s;

    m_s = y + v;

    return static_cast<MdFloat>(y + m_m2 * (x - y));
}
