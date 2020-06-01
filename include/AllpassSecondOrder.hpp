#ifndef MD_AUDIO_ALLPASS_SECOND_ORDER_HPP
#define MD_AUDIO_ALLPASS_SECOND_ORDER_HPP

#include "interfaces/Processable.hpp"
#include "zdf.hpp"

namespace md_audio {

    class AllpassSecondOrder : public Processable<MdFloat, MdFloat> {
    public:
        explicit AllpassSecondOrder();

        explicit AllpassSecondOrder(MdFloat);

        explicit AllpassSecondOrder(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_r(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s1 = 0.;
        double m_s2 = 0.;
        double m_g;
        double m_r2;
    };

    void AllpassSecondOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void AllpassSecondOrder::set_r(MdFloat r) noexcept {
        m_r2 = r2(static_cast<double>(r));
    }

}

#endif /* MD_AUDIO_ALLPASS_SECOND_ORDER_HPP */
