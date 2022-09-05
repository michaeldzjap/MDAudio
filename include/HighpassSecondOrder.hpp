#ifndef MD_AUDIO_HIGHPASS_SECOND_ORDER_HPP
#define MD_AUDIO_HIGHPASS_SECOND_ORDER_HPP

#include "Svf.hpp"

namespace md_audio {

    class HighpassSecondOrder : public Svf {
    public:
        explicit HighpassSecondOrder();

        explicit HighpassSecondOrder(double frequency);

        explicit HighpassSecondOrder(double frequency, double r);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_HIGHPASS_SECOND_ORDER_HPP */
