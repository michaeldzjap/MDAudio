#ifndef MD_AUDIO_UNIT_HPP
#define MD_AUDIO_UNIT_HPP

#include "types.hpp"

namespace md_audio {

    class Unit {
    public:
        static MdFloat get_sample_rate() noexcept;

        static void set_sample_rate(MdFloat sample_rate) noexcept;

        static MdFloat get_sample_duration() noexcept;

    protected:
        static MdFloat m_sample_rate;
        static MdFloat m_sample_duration;
    };

}

#endif /* MD_AUDIO_UNIT_HPP */
