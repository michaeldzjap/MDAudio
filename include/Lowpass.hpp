#ifndef MD_AUDIO_LOWPASS_HPP
#define MD_AUDIO_LOWPASS_HPP

#include "OnePole.hpp"
#include "Processable.hpp"
#include "Zdf.hpp"

namespace md_audio {

    class Lowpass : public Processable<MdFloat, MdFloat>, public Zdf, public OnePole {
    public:
        explicit Lowpass();

        explicit Lowpass(MdFloat);

        inline void set_frequency(MdFloat frequency) noexcept override final {
            Zdf::set_frequency(frequency);

            m_h = m_g / (1. + m_g);
        }

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_h;
    };

}

#endif /* MD_AUDIO_LOWPASS_HPP */
