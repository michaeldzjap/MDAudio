#ifndef MD_AUDIO_LOWPASS_SECOND_ORDER_HPP
#define MD_AUDIO_LOWPASS_SECOND_ORDER_HPP

#include "Svf.hpp"

namespace md_audio {

    class LowpassSecondOrder : public Svf {
    public:
        explicit LowpassSecondOrder();

        explicit LowpassSecondOrder(double frequency);

        explicit LowpassSecondOrder(double frequency, double r);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_LOWPASS_SECOND_ORDER_HPP */
