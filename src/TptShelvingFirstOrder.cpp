#include <cmath>
#include "TptShelvingFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::TptShelvingFirstOrder;

void TptShelvingFirstOrder::set_gain(double gain) noexcept {
     m_m2 = tpt::m2(gain);
}
