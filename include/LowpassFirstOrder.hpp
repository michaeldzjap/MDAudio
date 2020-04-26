#ifndef MD_AUDIO_LOWPASS_FIRST_ORDER_HPP
#define MD_AUDIO_LOWPASS_FIRST_ORDER_HPP

#include "Processable.hpp"
#include "zdf.hpp"

namespace md_audio {

    class LowpassFirstOrder : public Processable<MdFloat, MdFloat> {
    public:
        explicit LowpassFirstOrder();

        explicit LowpassFirstOrder(MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s = 0.;
        double m_g;
        double m_h;
    };

    void LowpassFirstOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
        m_h = m_g / (1. + m_g);
    }

}

#endif /* MD_AUDIO_LOWPASS_FIRST_ORDER_HPP */
