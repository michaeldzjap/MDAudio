#ifndef MD_AUDIO_BANDPASS_HPP
#define MD_AUDIO_BANDPASS_HPP

#include "Processable.hpp"
#include "zdf.hpp"

namespace md_audio {

    class Bandpass : public Processable<MdFloat, MdFloat> {
    public:
        explicit Bandpass();

        explicit Bandpass(MdFloat);

        explicit Bandpass(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_r(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s1 = 0.;
        double m_s2 = 0.;
        double m_g;
        double m_r2;
    };

    void Bandpass::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void Bandpass::set_r(MdFloat r) noexcept {
        m_r2 = r2(static_cast<double>(r));
    }

}

#endif /* MD_AUDIO_BANDPASS_HPP */
