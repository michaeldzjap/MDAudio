#ifndef MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP
#define MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP

#include "TptFilter.hpp"
#include "TptSecondOrder.hpp"
#include "TptShelving.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class LowshelfSecondOrder :
        public TptFilter,
        public TptSecondOrder,
        public TptShelving,
        public Processable<MdFloat, MdFloat>
    {
    public:
        explicit LowshelfSecondOrder();

        explicit LowshelfSecondOrder(MdFloat);

        explicit LowshelfSecondOrder(MdFloat, MdFloat);

        explicit LowshelfSecondOrder(MdFloat, MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_r(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s1 = 0.;
        double m_s2 = 0.;
        double m_g;
        double m_r2;
        double m_m2i;
        double m_m4i;
    };

    void LowshelfSecondOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void LowshelfSecondOrder::set_r(MdFloat r) noexcept {
        m_r2 = r2(static_cast<double>(r));
    }

    void LowshelfSecondOrder::set_gain(MdFloat gain) noexcept {
        m_m2i = 1. / m2(static_cast<double>(-gain));
        m_m4i = m_m2i * m_m2i;
    }

}

#endif /* MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP */
