#ifndef MD_AUDIO_IMPULSE_HPP
#define MD_AUDIO_IMPULSE_HPP

#include "SampleRate.hpp"
#include "interfaces/Generatable.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    class Impulse : public SampleRate, public Generatable<MdFloat> {
    public:
        explicit Impulse(MdFloat);

        inline void set_frequency(MdFloat frequency) noexcept {
            m_rate = m_sample_duration * utility::clip(
                frequency, static_cast<MdFloat>(0), static_cast<MdFloat>(sample_rate)
            );
        }

        MdFloat perform(void) noexcept override final;

    private:
        double m_phase = 1.;
        double m_rate;
    };

}

#endif /* MD_AUDIO_IMPULSE_HPP */
