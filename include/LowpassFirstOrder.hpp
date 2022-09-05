#ifndef MD_AUDIO_LOWPASS_FIRST_ORDER_HPP
#define MD_AUDIO_LOWPASS_FIRST_ORDER_HPP

#include "TptFirstOrder.hpp"
#include "Unit.hpp"

namespace md_audio {

    class LowpassFirstOrder : public Unit, public TptFirstOrder {
    public:
        explicit LowpassFirstOrder();

        explicit LowpassFirstOrder(double frequency);

        void set_frequency(double frequency) noexcept;

        double process(double in) noexcept;

    protected:
        double m_h;
    };

}

#endif /* MD_AUDIO_LOWPASS_FIRST_ORDER_HPP */
