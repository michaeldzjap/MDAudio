#ifndef MD_AUDIO_TILT_SECOND_ORDER_HPP
#define MD_AUDIO_TILT_SECOND_ORDER_HPP

#include "Processable.hpp"
#include "zdf.hpp"

namespace md_audio {

    class TiltSecondOrder : public Processable<MdFloat, MdFloat> {
    public:
        explicit TiltSecondOrder();

        explicit TiltSecondOrder(MdFloat);

        explicit TiltSecondOrder(MdFloat, MdFloat);

        explicit TiltSecondOrder(MdFloat, MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_r(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s1 = 0.;
        double m_s2 = 0.;
        double m_g;
        double m_r2;
        double m_m2;
        double m_m2i;
    };

    void TiltSecondOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void TiltSecondOrder::set_r(MdFloat r) noexcept {
        m_r2 = r2(static_cast<double>(r));
    }

    void TiltSecondOrder::set_gain(MdFloat gain) noexcept {
        m_m2 = m2(static_cast<double>(gain));
        m_m2i = 1. / m_m2;
    }

}

#endif /* MD_AUDIO_TILT_SECOND_ORDER_HPP */
