#ifndef MD_AUDIO_HIGHPASS_SECOND_ORDER_HPP
#define MD_AUDIO_HIGHPASS_SECOND_ORDER_HPP

#include "TptFilter.hpp"
#include "TptSecondOrder.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class HighpassSecondOrder :
        public TptFilter,
        public TptSecondOrder,
        public Processable<MdFloat, MdFloat>
    {
    public:
        explicit HighpassSecondOrder();

        explicit HighpassSecondOrder(MdFloat);

        explicit HighpassSecondOrder(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_r(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s1 = 0.;
        double m_s2 = 0.;
        double m_g;
        double m_r2;
    };

    void HighpassSecondOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void HighpassSecondOrder::set_r(MdFloat r) noexcept {
        m_r2 = r2(static_cast<double>(r));
    }

}

#endif /* MD_AUDIO_HIGHPASS_SECOND_ORDER_HPP */
