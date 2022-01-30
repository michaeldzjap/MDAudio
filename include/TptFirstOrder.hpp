#ifndef MD_AUDIO_TPT_FIRST_ORDER_HPP
#define MD_AUDIO_TPT_FIRST_ORDER_HPP

#include "Unit.hpp"

namespace md_audio {

    class TptFirstOrder : public Unit {
    public:
        void set_frequency(double frequency) noexcept;

    protected:
        double m_s = 0.;
        double m_h;
    };

}

#endif /* MD_AUDIO_TPT_FIRST_ORDER_HPP */
