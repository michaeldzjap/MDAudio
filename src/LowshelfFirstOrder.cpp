#include "LowshelfFirstOrder.hpp"

using md_audio::LowshelfFirstOrder;
using md_audio::MdFloat;

LowshelfFirstOrder::LowshelfFirstOrder() {
    set_frequency(static_cast<MdFloat>(440));
    set_gain(static_cast<MdFloat>(0));
}

LowshelfFirstOrder::LowshelfFirstOrder(MdFloat frequency) {
    set_frequency(frequency);
    set_gain(static_cast<MdFloat>(0));
}

LowshelfFirstOrder::LowshelfFirstOrder(MdFloat frequency, MdFloat gain) {
    set_frequency(frequency);
    set_gain(gain);
}

MdFloat LowshelfFirstOrder::perform(MdFloat in) noexcept {
    auto x = static_cast<double>(in);
    auto v = (x - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return static_cast<MdFloat>(m_m2i * y + x - y);
}
