#ifndef MD_AUDIO_SINE_OSCILLATOR_HPP
#define MD_AUDIO_SINE_OSCILLATOR_HPP

#include "Oscillator.hpp"

namespace md_audio {

    class SineOscillator : public Oscillator {
    public:
        explicit SineOscillator();

        explicit SineOscillator(double frequency);

        explicit SineOscillator(double frequency, double phase);

        double process() noexcept;
    };

}

#endif /* MD_AUDIO_SINE_OSCILLATOR_HPP */
