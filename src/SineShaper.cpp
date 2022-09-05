#include "SineShaper.hpp"
#include "utility.hpp"

using md_audio::SineShaper;
using md_audio::utility::lookup;

SineShaper::SineShaper(double limit) {
    set_limit(limit);
}

void SineShaper::set_limit(double limit) noexcept {
    if (limit != 0.) {
        m_limit = limit;
        m_phase_rate = 1. / m_limit * RADIANS_TO_INCREMENT;
    }
}

double SineShaper::process(double in) noexcept {
    auto offset = in * m_phase_rate;

    while (offset < 0.) offset += TABLE_SIZE;
    while (offset >= TABLE_SIZE) offset -= TABLE_SIZE;

    return m_limit * utility::lookup(sine_table, offset);
}
