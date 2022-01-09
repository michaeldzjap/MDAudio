#include <cmath>
#include "TptFirstOrder.hpp"
#include "constants.hpp"
#include "utility.hpp"

using md_audio::TptFirstOrder;

double TptFirstOrder::g(double frequency) noexcept {
    return std::tan(utility::clip(frequency, 0., m_half_sample_rate) * PI * m_sample_duration);
}
