#ifndef MD_AUDIO_TILT_SECOND_ORDER_HPP
#define MD_AUDIO_TILT_SECOND_ORDER_HPP

#include "TptSecondOrder.hpp"

namespace md_audio {

    class TiltSecondOrder : public TptSecondOrder {
    public:
        explicit TiltSecondOrder();

        explicit TiltSecondOrder(double frequency);

        explicit TiltSecondOrder(double frequency, double r);

        explicit TiltSecondOrder(double frequency, double r, double gain);

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_m2;
        double m_m2i;
    };

}

#endif /* MD_AUDIO_TILT_SECOND_ORDER_HPP */
