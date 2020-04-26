#include "LowpassFirstOrder.hpp"

using md_audio::LowpassFirstOrder;
using md_audio::MdFloat;

LowpassFirstOrder::LowpassFirstOrder() {
    set_frequency(static_cast<MdFloat>(440));
}

LowpassFirstOrder::LowpassFirstOrder(MdFloat frequency) {
    set_frequency(frequency);
}

MdFloat LowpassFirstOrder::perform(MdFloat in) noexcept {
    auto v = (static_cast<double>(in) - m_s) * m_h;
    auto y = v + m_s;

    m_s = y + v;

    return static_cast<MdFloat>(y);
}
