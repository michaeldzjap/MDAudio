#ifndef MD_AUTIO_TILT_FIRST_ORDER_HPP
#define MD_AUTIO_TILT_FIRST_ORDER_HPP

#include "TptFirstOrder.hpp"
#include "TptShelving.hpp"

namespace md_audio {

    class TiltFirstOrder : public TptFirstOrder, public TptShelving {
    public:
        explicit TiltFirstOrder();

        explicit TiltFirstOrder(double frequency);

        explicit TiltFirstOrder(double frequency, double gain);

        void set_frequency(double frequency) noexcept;

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_g;
        double m_m;
        double m_mi;
    };

}

#endif /* MD_AUTIO_TILT_FIRST_ORDER_HPP */
