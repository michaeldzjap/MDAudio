#ifndef MD_AUDIO_ALLPASS_FIRST_ORDER_HPP
#define MD_AUDIO_ALLPASS_FIRST_ORDER_HPP

#include "TptFilter.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class AllpassFirstOrder : public TptFilter, public Processable<MdFloat, MdFloat> {
    public:
        explicit AllpassFirstOrder();

        explicit AllpassFirstOrder(MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s = 0.;
        double m_g;
    };

    void AllpassFirstOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

}

#endif /* MD_AUDIO_ALLPASS_FIRST_ORDER_HPP */
