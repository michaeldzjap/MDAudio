#ifndef MD_AUDIO_GAINABLE_HPP
#define MD_AUDIO_GAINABLE_HPP

#include "utility.hpp"

using md_audio::utility::clip;

namespace md_audio {

    class Gainable {
    public:
        void set_gain(double gain) noexcept {
            m_gain = clip(gain, 0., 1.);
        }

    protected:
        double m_gain;
    };

}

#endif /* MD_AUDIO_GAINABLE_HPP */
