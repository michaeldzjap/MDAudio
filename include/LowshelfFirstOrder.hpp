#ifndef MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP
#define MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP

#include "Processable.hpp"
#include "zdf.hpp"

namespace md_audio {

    class LowshelfFirstOrder : public Processable<MdFloat, MdFloat> {
    public:
        explicit LowshelfFirstOrder();

        explicit LowshelfFirstOrder(MdFloat);

        explicit LowshelfFirstOrder(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s = 0.;
        double m_g;
        double m_h;
        double m_m2;
        double m_m2i;
    };

    void LowshelfFirstOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
        m_h = m_g / (1. + m_g);
    }

    void LowshelfFirstOrder::set_gain(MdFloat gain) noexcept {
        m_m2 = m2(static_cast<double>(-gain));
        m_m2i = 1. / m_m2;
    }

}

#endif /* MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP */
