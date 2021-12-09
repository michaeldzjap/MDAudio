#ifndef MD_AUDIO_HANN_OSCILLATOR_HPP
#define MD_AUDIO_HANN_OSCILLATOR_HPP

#include "Oscillator.hpp"

namespace md_audio {

    class HannOscillator : public Oscillator {
    public:
        HannOscillator(double frequency);

        HannOscillator(double frequency, double phase);

        double process() noexcept;
    };

}

#endif /* MD_AUDIO_HANN_OSCILLATOR_HPP */
