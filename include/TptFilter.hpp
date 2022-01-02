#ifndef MD_AUDIO_TPT_FILTER_HPP
#define MD_AUDIO_TPT_FILTER_HPP

#include "Unit.hpp"

namespace md_audio {

    class TptFilter : public Unit {
    protected:
        double m_s = 0.;

        static double g(double frequency) noexcept;
    };

}

#endif /* MD_AUDIO_TPT_FILTER_HPP */
