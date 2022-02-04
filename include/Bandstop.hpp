#ifndef MD_AUDIO_BANDSTOP_HPP
#define MD_AUDIO_BANDSTOP_HPP

#include "Svf.hpp"

namespace md_audio {

    class Bandstop : public Svf {
    public:
        explicit Bandstop();

        explicit Bandstop(double frequency);

        explicit Bandstop(double frequency, double r);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_BANDSTOP_HPP */
