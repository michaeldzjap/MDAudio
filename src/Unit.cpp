#include "Unit.hpp"

using md_audio::MdFloat;
using md_audio::Unit;

MdFloat Unit::m_sample_rate = 44100.;
MdFloat Unit::m_sample_duration = 1. / 44100.;

MdFloat Unit::get_sample_rate() noexcept {
    return m_sample_rate;
}

void Unit::set_sample_rate(MdFloat sample_rate) noexcept {
    if (sample_rate > .0 && sample_rate != m_sample_rate) {
        m_sample_rate = sample_rate;
        m_sample_duration = 1. / sample_rate;
    }
}

MdFloat Unit::get_sample_duration() noexcept {
    return m_sample_duration;
}
