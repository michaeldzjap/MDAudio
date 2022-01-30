#include <cmath>
#include "ShelvingFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::ShelvingFirstOrder;

void ShelvingFirstOrder::set_gain(double gain) noexcept {
     m_m2 = tpt::m2(gain);
}
