#ifndef MD_AUDIO_TPT_FIRST_ORDER_HPP
#define MD_AUDIO_TPT_FIRST_ORDER_HPP

#include "Unit.hpp"

namespace md_audio {

    class TptFirstOrder : public Unit {
    protected:
        double m_s = 0.;

        static double g(double frequency) noexcept;
    };

}

#endif /* MD_AUDIO_TPT_FIRST_ORDER_HPP */
