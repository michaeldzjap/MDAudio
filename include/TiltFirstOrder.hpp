#ifndef MD_AUDIO_TILT_FIRST_ORDER_HPP
#define MD_AUDIO_TILT_FIRST_ORDER_HPP

#include "LowpassFirstOrder.hpp"
#include "ShelvingFirstOrder.hpp"

namespace md_audio {

    class TiltFirstOrder : public LowpassFirstOrder, public ShelvingFirstOrder {
    public:
        explicit TiltFirstOrder();

        explicit TiltFirstOrder(double frequency);

        explicit TiltFirstOrder(double frequency, double gain);

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_m;
        double m_mi;
    };

}

#endif /* MD_AUDIO_TILT_FIRST_ORDER_HPP */
