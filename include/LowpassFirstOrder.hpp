#ifndef MD_AUDIO_LOWPASS_FIRST_ORDER_HPP
#define MD_AUDIO_LOWPASS_FIRST_ORDER_HPP

#include "TptFirstOrder.hpp"

namespace md_audio {

    class LowpassFirstOrder : public TptFirstOrder {
    public:
        explicit LowpassFirstOrder();

        explicit LowpassFirstOrder(double frequency);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_LOWPASS_FIRST_ORDER_HPP */
