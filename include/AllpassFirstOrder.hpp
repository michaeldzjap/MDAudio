#ifndef MD_AUDIO_ALLPASS_FIRST_ORDER_HPP
#define MD_AUDIO_ALLPASS_FIRST_ORDER_HPP

#include "LowpassFirstOrder.hpp"

namespace md_audio {

    class AllpassFirstOrder : public LowpassFirstOrder {
    public:
        explicit AllpassFirstOrder();

        explicit AllpassFirstOrder(double frequency);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_ALLPASS_FIRST_ORDER_HPP */
