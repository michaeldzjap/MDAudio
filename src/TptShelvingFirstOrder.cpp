#include <cmath>
#include "TptShelvingFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::TptShelvingFirstOrder;

void TptShelvingFirstOrder::set_frequency(double frequency) noexcept {
    auto g = tpt::g(frequency, m_half_sample_rate, m_sample_duration);
    m_h = g / (1. + g);
}

void TptShelvingFirstOrder::set_gain(double gain) noexcept {
     m_m2 = tpt::m2(gain);
}
