#ifndef MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP
#define MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP

#include "TptFilter.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class HighpassFirstOrder : public TptFilter, public Processable<MdFloat, MdFloat> {
    public:
        explicit HighpassFirstOrder();

        explicit HighpassFirstOrder(MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s = 0.;
        double m_g;
        double m_g2;
        double m_h;
    };

    void HighpassFirstOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
        m_g2 = m_g + m_g;
        m_h = 1. / (1. + m_g);
    }

}

#endif /* MD_AUDIO_HIGHPASS_FIRST_ORDER_HPP */
