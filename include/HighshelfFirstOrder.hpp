#ifndef MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP
#define MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP

#include "Processable.hpp"
#include "zdf.hpp"

namespace md_audio {

    class HighshelfFirstOrder : public Processable<MdFloat, MdFloat> {
    public:
        explicit HighshelfFirstOrder();

        explicit HighshelfFirstOrder(MdFloat);

        explicit HighshelfFirstOrder(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s = 0.;
        double m_g;
        double m_h;
        double m_m2;
    };

    void HighshelfFirstOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
        m_h = m_g / (1. + m_g);
    }

    void HighshelfFirstOrder::set_gain(MdFloat gain) noexcept {
        m_m2 = m2(static_cast<double>(gain));
    }

}

#endif /* MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP */
