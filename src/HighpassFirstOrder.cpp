#include "HighpassFirstOrder.hpp"

using md_audio::HighpassFirstOrder;
using md_audio::MdFloat;

HighpassFirstOrder::HighpassFirstOrder() {
    set_frequency(static_cast<MdFloat>(440));
}

HighpassFirstOrder::HighpassFirstOrder(MdFloat frequency) {
    set_frequency(frequency);
}

MdFloat HighpassFirstOrder::perform(MdFloat in) noexcept {
    auto y = (static_cast<double>(in) - m_s) * m_h;

    m_s = m_s + y * m_g2;

    return static_cast<MdFloat>(y);
}
