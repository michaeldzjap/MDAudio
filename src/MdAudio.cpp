#include "MdAudio.hpp"
#include "constants.hpp"

using md_audio::MdAudio;

double MdAudio::m_sample_rate = md_audio::sample_rate;
double MdAudio::m_sample_duration = md_audio::sample_duration;

double MdAudio::get_sample_rate() noexcept {
    return m_sample_rate;
}

void MdAudio::set_sample_rate(double new_sample_rate) noexcept {
    if (new_sample_rate > 0 && new_sample_rate != m_sample_rate) {
        m_sample_rate = new_sample_rate;
        m_half_sample_rate = m_sample_rate * .5;
        m_sample_duration = 1. / m_sample_rate;
        m_pi_over_sample_rate = md_audio::pi * m_sample_duration;
    }
}

double MdAudio::get_half_sample_rate() noexcept {
    return m_half_sample_rate;
}

double MdAudio::get_sample_duration() noexcept {
    return m_sample_duration;
}

double MdAudio::get_pi_over_sample_rate() noexcept {
    return m_pi_over_sample_rate;
}

MdAudio::~MdAudio() {}
