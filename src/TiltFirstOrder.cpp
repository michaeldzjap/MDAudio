#include "TiltFirstOrder.hpp"

using md_audio::TiltFirstOrder;
using md_audio::MdFloat;

TiltFirstOrder::TiltFirstOrder() {
    set_frequency(static_cast<MdFloat>(440));
}

TiltFirstOrder::TiltFirstOrder(MdFloat frequency) {
    set_frequency(frequency);
}

MdFloat TiltFirstOrder::perform(MdFloat in) noexcept {
    auto x = static_cast<double>(in);
    auto v = (x - m_s) * m_g / (1. + m_g);
    auto y = v + m_s;

    m_s = y + v;

    return static_cast<MdFloat>(m_mi * y + m_m * (x - y));
}
