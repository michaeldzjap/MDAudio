#ifndef MD_AUDIO_BANDSHELF_HPP
#define MD_AUDIO_BANDSHELF_HPP

#include "Processable.hpp"
#include "zdf.hpp"

namespace md_audio {

    class Bandshelf : public Processable<MdFloat, MdFloat> {
    public:
        explicit Bandshelf();

        explicit Bandshelf(MdFloat);

        explicit Bandshelf(MdFloat, MdFloat);

        explicit Bandshelf(MdFloat, MdFloat, MdFloat);

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
    };

    void Bandshelf::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void Bandshelf::set_r(MdFloat r) noexcept {
        m_r2 = r2(static_cast<double>(r));
    }

    void Bandshelf::set_gain(MdFloat gain) noexcept {
        m_m2i = 1. / m2(static_cast<double>(-gain));
    }

}

#endif /* MD_AUDIO_BANDSHELF_HPP */
