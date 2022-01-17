#ifndef MD_AUDIO_BANDPASS_HPP
#define MD_AUDIO_BANDPASS_HPP

#include "TptSecondOrder.hpp"

namespace md_audio {

    class Bandpass : public TptSecondOrder {
    public:
        explicit Bandpass();

        explicit Bandpass(double frequency);

        explicit Bandpass(double frequency, double r);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_BANDPASS_HPP */
