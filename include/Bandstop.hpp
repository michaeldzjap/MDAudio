#ifndef MD_AUDIO_BANDSTOP_HPP
#define MD_AUDIO_BANDSTOP_HPP

#include "TptSecondOrder.hpp"

namespace md_audio {

    class Bandstop : public TptSecondOrder {
    public:
        explicit Bandstop();

        explicit Bandstop(double frequency);

        explicit Bandstop(double frequency, double r);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_BANDSTOP_HPP */
