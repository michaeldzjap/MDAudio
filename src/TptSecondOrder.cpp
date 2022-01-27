#include "TptSecondOrder.hpp"
#include "tpt.hpp"
#include "utility.hpp"

using md_audio::TptSecondOrder;

void TptSecondOrder::set_frequency(double frequency) noexcept {
    m_g = tpt::g(frequency, m_half_sample_rate, m_sample_duration);
}

void TptSecondOrder::set_r(double r) noexcept {
    m_r2 = tpt::r2(r);
}
