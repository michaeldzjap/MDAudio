#ifndef MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP
#define MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP

#include "TptFilter.hpp"
#include "TptSecondOrder.hpp"
#include "TptShelving.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class HighShelfSecondOrder :
        public TptFilter,
        public TptSecondOrder,
        public TptShelving,
        public Processable<MdFloat, MdFloat>
    {
    public:
        explicit HighShelfSecondOrder();

        explicit HighShelfSecondOrder(MdFloat);

        explicit HighShelfSecondOrder(MdFloat, MdFloat);

        explicit HighShelfSecondOrder(MdFloat, MdFloat, MdFloat);

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
        double m_m4;
    };

    void HighShelfSecondOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void HighShelfSecondOrder::set_r(MdFloat r) noexcept {
        m_r2 = r2(static_cast<double>(r));
    }

    void HighShelfSecondOrder::set_gain(MdFloat gain) noexcept {
        m_m2 = m2(static_cast<double>(gain));
        m_m4 = m_m2 * m_m2;
    }

}

#endif /* MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP */
