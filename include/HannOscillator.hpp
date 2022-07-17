#ifndef MD_AUDIO_HANN_OSCILLATOR_HPP
#define MD_AUDIO_HANN_OSCILLATOR_HPP

#include "Oscillator.hpp"

namespace md_audio {

    class HannOscillator : public Oscillator {
    public:
        explicit HannOscillator();

        explicit HannOscillator(double frequency);

        explicit HannOscillator(double frequency, double phase);

        double process() noexcept;
    };

}

#endif /* MD_AUDIO_HANN_OSCILLATOR_HPP */
