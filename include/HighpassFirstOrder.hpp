#ifndef MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP
#define MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP

#include "TptFirstOrder.hpp"

namespace md_audio {

    class HighpassFirstOrder : public TptFirstOrder {
    public:
        explicit HighpassFirstOrder();

        explicit HighpassFirstOrder(double frequency);

        void set_frequency(double frequency) noexcept;

        double process(double in) noexcept;

    private:
        double m_h;
        double m_g2;
    };

}

#endif /* MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP */
