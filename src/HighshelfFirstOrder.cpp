#include "HighshelfFirstOrder.hpp"

using md_audio::HighshelfFirstOrder;
using md_audio::MdFloat;

HighshelfFirstOrder::HighshelfFirstOrder() {
    set_frequency(static_cast<MdFloat>(440));
    set_gain(static_cast<MdFloat>(0));
}

HighshelfFirstOrder::HighshelfFirstOrder(MdFloat frequency) {
    set_frequency(frequency);
    set_gain(static_cast<MdFloat>(0));
}

HighshelfFirstOrder::HighshelfFirstOrder(MdFloat frequency, MdFloat gain) {
    set_frequency(frequency);
    set_gain(gain);
}

MdFloat HighshelfFirstOrder::perform(MdFloat in) noexcept {
    auto x = static_cast<double>(in);
    auto v = (x - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return static_cast<MdFloat>(y + m_m2 * (x - y));
}
