#ifndef MD_AUDIO_IMPULSE_HPP
#define MD_AUDIO_IMPULSE_HPP

#include "Generatable.hpp"
#include "constants.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    class Impulse : public Generatable<MdFloat> {
    public:
        explicit Impulse(MdFloat);

        inline void set_frequency(MdFloat frequency) noexcept {
            m_rate = sample_duration * utility::clip(frequency, static_cast<MdFloat>(0), static_cast<MdFloat>(sample_rate));
        }

        MdFloat perform(void) noexcept override final;

    private:
        double m_phase = 1.;
        double m_rate;
    };

}

#endif /* MD_AUDIO_IMPULSE_HPP */
