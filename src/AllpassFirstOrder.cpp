#include "AllpassFirstOrder.hpp"

using md_audio::AllpassFirstOrder;
using md_audio::MdFloat;

AllpassFirstOrder::AllpassFirstOrder() {
    set_frequency(static_cast<MdFloat>(440));
}

AllpassFirstOrder::AllpassFirstOrder(MdFloat frequency) {
    set_frequency(frequency);
}

MdFloat AllpassFirstOrder::perform(MdFloat in) noexcept {
    auto xs = static_cast<double>(in) - m_s;

    m_s = m_s + xs * (2. * m_g / (1. + m_g));

    return static_cast<MdFloat>(m_s - xs);
}
