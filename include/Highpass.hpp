#ifndef MD_AUDIO_HIGHPASS_HPP
#define MD_AUDIO_HIGHPASS_HPP

#include "OnePole.hpp"
#include "Processable.hpp"
#include "Zdf.hpp"

namespace md_audio {

    class Highpass : public Processable<MdFloat, MdFloat>, public Zdf, public OnePole {
    public:
        explicit Highpass();

        explicit Highpass(MdFloat);

        inline void set_frequency(MdFloat frequency) noexcept override final {
            Zdf::set_frequency(frequency);

            m_g2 = m_g + m_g;
            m_h = 1. / (1. + m_g);
        }

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_g2;
        double m_h;
    };

}

#endif /* MD_AUDIO_HIGHPASS_HPP */
