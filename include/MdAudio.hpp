#ifndef MD_AUDIO_MD_AUDIO_HPP
#define MD_AUDIO_MD_AUDIO_HPP

#include "types.hpp"

namespace md_audio {

    class MdAudio {
    public:
        static double get_sample_rate() noexcept;

        static void set_sample_rate(double) noexcept;

        static double get_half_sample_rate() noexcept;

        static double get_sample_duration() noexcept;

        static double get_pi_over_sample_rate() noexcept;

        virtual ~MdAudio() = 0;

    private:
        static double m_sample_rate;
        static double m_half_sample_rate;
        static double m_sample_duration;
        static double m_pi_over_sample_rate;
    };

}

#endif /* MD_AUDIO_MD_AUDIO_HPP */
