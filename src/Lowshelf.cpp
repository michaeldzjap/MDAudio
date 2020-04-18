#include "Lowshelf.hpp"
#include "Shelving.hpp"

using md_audio::Lowshelf;
using md_audio::MdFloat;
using md_audio::Shelving;

Lowshelf::Lowshelf() {
    set_frequency(static_cast<MdFloat>(440));
}

Lowshelf::Lowshelf(MdFloat frequency) {
    set_frequency(frequency);
}

Lowshelf::Lowshelf(MdFloat frequency, MdFloat gain) : Shelving(-gain) {
    set_frequency(frequency);
}

MdFloat Lowshelf::perform(MdFloat in) noexcept {
    const double x = static_cast<double>(in);
    const double v = (x - m_s) * m_h;
    const double y = v + m_s;

    m_s = y + v;

    return static_cast<MdFloat>(m_m2i * y + x - y);
}
