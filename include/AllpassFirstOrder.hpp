#ifndef MD_AUDIO_ALLPASS_FIRST_ORDER_HPP
#define MD_AUDIO_ALLPASS_FIRST_ORDER_HPP

#include "TptFirstOrder.hpp"

namespace md_audio {

    class AllpassFirstOrder : public TptFirstOrder {
    public:
        explicit AllpassFirstOrder();

        explicit AllpassFirstOrder(double frequency);

        void set_frequency(double frequency) noexcept;

        double process(double in) noexcept;

    private:
        double m_h;
    };

}

#endif /* MD_AUDIO_ALLPASS_FIRST_ORDER_HPP */
