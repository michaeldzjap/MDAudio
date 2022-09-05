#ifndef MD_AUDIO_ALLPASS_SECOND_ORDER_HPP
#define MD_AUDIO_ALLPASS_SECOND_ORDER_HPP

#include "Svf.hpp"

namespace md_audio {

    class AllpassSecondOrder : public Svf {
    public:
        explicit AllpassSecondOrder();

        explicit AllpassSecondOrder(double frequency);

        explicit AllpassSecondOrder(double frequency, double r);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_ALLPASS_SECOND_ORDER_HPP */
