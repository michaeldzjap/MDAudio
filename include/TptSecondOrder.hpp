#ifndef MD_AUDIO_TPT_SECOND_ORDER_HPP
#define MD_AUDIO_TPT_SECOND_ORDER_HPP

#include "TptFirstOrder.hpp"

namespace md_audio {

    class TptSecondOrder : public TptFirstOrder {
    public:
        void set_frequency(double frequency) noexcept;

        void set_r(double r) noexcept;

    protected:
        double m_s2 = 0.;
        double m_g;
        double m_r2;

        static double r2(double r) noexcept;

        static double d(double r2, double g) noexcept;
    };

}

#endif /* MD_AUDIO_TPT_SECOND_ORDER_HPP */
