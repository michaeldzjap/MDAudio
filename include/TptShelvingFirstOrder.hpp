#ifndef MD_AUDIO_TPT_SHELVING_FIRST_ORDER_HPP
#define MD_AUDIO_TPT_SHELVING_FIRST_ORDER_HPP

#include "TptFirstOrder.hpp"

namespace md_audio {

    class TptShelvingFirstOrder : public TptFirstOrder {
    public:
        void set_frequency(double frequency) noexcept;

        void set_gain(double gain) noexcept;

    protected:
        double m_h;
        double m_m2;
    };

}

#endif /* MD_AUDIO_TPT_SHELVING_FIRST_ORDER_HPP */
