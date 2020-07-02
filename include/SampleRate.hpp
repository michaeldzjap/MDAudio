#ifndef MD_AUDIO_SAMPLE_RATE_HPP
#define MD_AUDIO_SAMPLE_RATE_HPP

#include "types.hpp"

namespace md_audio {

    class SampleRate {
    public:
        static double get_sample_rate() noexcept;

        static void set_sample_rate(double) noexcept;

        static double get_sample_duration() noexcept;

        virtual ~SampleRate() = 0;

    protected:
        static double m_sample_rate;
        static double m_half_sample_rate;
        static double m_sample_duration;
        static double m_pi_over_sample_rate;
        static double m_cycles_to_increment;
    };

}

#endif /* MD_AUDIO_SAMPLE_RATE_HPP */
