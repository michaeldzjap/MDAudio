#ifndef MD_AUDIO_LOWPASS_FIRST_ORDER_HPP
#define MD_AUDIO_LOWPASS_FIRST_ORDER_HPP

#include "Unit.hpp"

namespace md_audio {

    class LowpassFirstOrder : public Unit {
    public:
        explicit LowpassFirstOrder();

        explicit LowpassFirstOrder(double frequency);

        void set_frequency(double frequency) noexcept;

        double process(double in) noexcept;

    protected:
        double m_s = 0.;
        double m_h;
    };

}

#endif /* MD_AUDIO_LOWPASS_FIRST_ORDER_HPP */
