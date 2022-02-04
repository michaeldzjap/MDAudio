#ifndef MD_AUDIO_TILT_SECOND_ORDER_HPP
#define MD_AUDIO_TILT_SECOND_ORDER_HPP

#include "ShelvingSecondOrder.hpp"
#include "Svf.hpp"

namespace md_audio {

    class TiltSecondOrder : public Svf, public ShelvingSecondOrder {
    public:
        explicit TiltSecondOrder();

        explicit TiltSecondOrder(double frequency);

        explicit TiltSecondOrder(double frequency, double r);

        explicit TiltSecondOrder(double frequency, double r, double gain);

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_TILT_SECOND_ORDER_HPP */
