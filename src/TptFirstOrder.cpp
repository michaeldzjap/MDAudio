#include "TptFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::TptFirstOrder;

void TptFirstOrder::set_frequency(double frequency) noexcept {
    auto g = tpt::g(frequency, m_half_sample_rate, m_sample_duration);
    m_h = g / (1. + g);
}
