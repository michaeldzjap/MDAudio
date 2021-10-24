#include "Unit.hpp"

using md_audio::Unit;

double Unit::m_sample_rate = 44100.;
double Unit::m_sample_duration = 1. / 44100.;

double Unit::get_sample_rate() noexcept {
    return m_sample_rate;
}

void Unit::set_sample_rate(double sample_rate) noexcept {
    if (sample_rate > .0 && sample_rate != m_sample_rate) {
        m_sample_rate = sample_rate;
        m_sample_duration = 1. / sample_rate;
    }
}

double Unit::get_sample_duration() noexcept {
    return m_sample_duration;
}
