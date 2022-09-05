#ifndef MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP
#define MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP

#include "LowpassFirstOrder.hpp"

namespace md_audio {

    class HighpassFirstOrder : public LowpassFirstOrder {
    public:
        explicit HighpassFirstOrder();

        explicit HighpassFirstOrder(double frequency);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP */
