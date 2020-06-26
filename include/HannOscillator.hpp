#ifndef MD_AUDIO_HANN_OSCILLATOR_HPP
#define MD_AUDIO_HANN_OSCILLATOR_HPP

#include "Oscillator.hpp"
#include "constants.hpp"
#include "interfaces/Generatable.hpp"
#include "types.hpp"

namespace md_audio {

    class HannOscillator : public Generatable<MdFloat>, public Oscillator {
    public:
        explicit HannOscillator();

        explicit HannOscillator(MdFloat);

        explicit HannOscillator(MdFloat, MdFloat);

        MdFloat perform(void) noexcept override final;
    };

}

#endif /* MD_AUDIO_HANN_OSCILLATOR_HPP */
