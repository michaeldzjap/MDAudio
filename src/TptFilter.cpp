#include <cmath>
#include "TptFilter.hpp"
#include "constants.hpp"
#include "utility.hpp"

using md_audio::TptFilter;

double TptFilter::g(double frequency) noexcept {
    return std::tan(utility::clip(frequency, 0., m_half_sample_rate) * PI * m_sample_duration);
}
