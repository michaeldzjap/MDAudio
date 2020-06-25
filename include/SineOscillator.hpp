#ifndef MD_AUDIO_SINE_OSCILLATOR_HPP
#define MD_AUDIO_SINE_OSCILLATOR_HPP

#include "Oscillator.hpp"
#include "constants.hpp"
#include "interfaces/Generatable.hpp"
#include "types.hpp"

namespace md_audio {

    class SineOscillator : public Oscillator, public Generatable<MdFloat> {
    public:
        SineOscillator() = default;

        explicit SineOscillator(MdFloat);

        explicit SineOscillator(MdFloat, MdFloat);

        MdFloat perform(void) noexcept override final;
    };

}

#endif /* MD_AUDIO_SINE_OSCILLATOR_HPP */
