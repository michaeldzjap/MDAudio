#include "ShelvingSecondOrder.hpp"
#include "tpt.hpp"

using md_audio::ShelvingSecondOrder;

void ShelvingSecondOrder::set_gain(double gain) noexcept {
    m_m2 = tpt::m2(gain);
    m_m4 = m_m2 * m_m2;
}
